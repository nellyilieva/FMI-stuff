use std::collections::HashMap;
use std::convert::TryFrom;
use std::env;
use std::error::Error;
use std::fs::{self, File};
use std::io::{self, BufRead, BufReader, Read};
use std::path::Path;
use std::process;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
enum LogLevel {
    Error,
    Warn,
    Info,
    Debug,
}

struct AggregateInfo {
    log_counts: HashMap<LogLevel, usize>,
    skipped_files: Vec<String>,
}

#[derive(Debug)]
enum ParseLogError {
    Read(io::Error),
    ParseLine,
    UnknownLevel(String),
}

impl From<io::Error> for ParseLogError {
    fn from(err: io::Error) -> Self {
        ParseLogError::Read(err)
    }
}

impl Error for ParseLogError {}

impl std::fmt::Display for ParseLogError {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        match self {
            ParseLogError::Read(e) => write!(f, "I/O error: {}", e),
            ParseLogError::ParseLine => write!(f, "Invalid log format"),
            ParseLogError::UnknownLevel(level) => write!(f, "Unknown log level: {}", level),
        }
    }
}

impl TryFrom<&str> for LogLevel {
    type Error = String;

    fn try_from(value: &str) -> Result<Self, String> {
        match value {
            "ERROR" => Ok(LogLevel::Error),
            "WARN" => Ok(LogLevel::Warn),
            "INFO" => Ok(LogLevel::Info),
            "DEBUG" => Ok(LogLevel::Debug),
            _ => Err(value.to_string()),
        }
    }
}

impl LogLevel {
    fn as_str(&self) -> &'static str {
        match self {
            LogLevel::Error => "Error",
            LogLevel::Warn => "Warn",
            LogLevel::Info => "Info",
            LogLevel::Debug => "Debug",
        }
    }
}

fn parse_log_file<R>(file: R, map: &mut HashMap<LogLevel, usize>) -> Result<(), ParseLogError>
where
    R: Read,
{
    let reader = BufReader::new(file);

    for line_result in reader.lines() {
        let line = line_result?;

        let trimmed = line.trim();
        if trimmed.is_empty() {
            continue;
        }

        if let Some(space_pos) = trimmed.find(' ') {
            let level_str = &trimmed[..space_pos];

            let level = LogLevel::try_from(level_str).map_err(|err| ParseLogError::UnknownLevel(err))?;
            *map.entry(level).or_insert(0) += 1;
        }
        else {
            return Err(ParseLogError::ParseLine);
        }
    }

    Ok(())
}

fn aggregate_logs(dir: &Path) -> Result<AggregateInfo, Box<dyn Error>> {
    let mut log_counts = HashMap::new();
    let mut skipped_files = Vec::new();

    if !dir.exists() {
        return Err(format!("Directory does not exist: {}", dir.display()).into());
    }

    if !dir.is_dir() {
        return Err(format!("Path is not a directory: {}", dir.display()).into());
    }

    for entry in fs::read_dir(dir)? {
        let entry = entry?;
        let path = entry.path();

        if path.extension().map_or(false, |ext| ext == "log") {
            let filename = path
                .file_name()
                .unwrap_or_default()
                .to_string_lossy()
                .to_string();

            let metadata = fs::metadata(&path)?;
            let file_size = metadata.len();
            
            let result: Result<(), ParseLogError> = if file_size > 10 * 1024 {
                let file = File::open(&path)?;
                parse_log_file(file, &mut log_counts)
            }
            else {
                let content = fs::read_to_string(&path)?;
                let cursor = io::Cursor::new(content);
                parse_log_file(cursor, &mut log_counts)
            };

            if let Err(e) = result {
                skipped_files.push(format!("{}: {}", filename, e));
            }
        }
    }

    Ok(AggregateInfo {
        log_counts,
        skipped_files,
    })
}

fn main() {
    let args: Vec<String> = env::args().collect();

    if args.len() != 2 {
        eprintln!("Usage: {} <path_to_log_directory>", args[0]);
        eprintln!("Example: {} ./logs", args[0]);
        process::exit(1);
    }

    let dir_path = Path::new(&args[1]);

    match aggregate_logs(dir_path) {
        Ok(info) => {
            println!("Statistics:");

            let levels = [
                LogLevel::Debug,
                LogLevel::Info,
                LogLevel::Warn,
                LogLevel::Error,
            ];

            for level in levels.iter() {
                let count = info.log_counts.get(level).unwrap_or(&0);
                println!("     {}: {}", level.as_str(), count);
            }

            if !info.skipped_files.is_empty() {
                println!("\nSkipped files:");
                for file in info.skipped_files {
                    println!("     {}", file);
                }
            }
        }
        Err(e) => {
            eprintln!("Error: {}", e);
            process::exit(1);
        }
    }
}