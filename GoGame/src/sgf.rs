use winnow::{
    Parser,
    ascii::{alpha1, alphanumeric1},
    combinator::{delimited, opt, preceded, repeat},
    token::{any, take_while},
};

use crate::types::{Position, Stone};

#[derive(Debug, Clone, PartialEq, Eq)]
pub enum SgfMove {
    BlackMove(Position),
    WhiteMove(Position),
}

#[derive(Debug, Clone)]
pub struct SgfGame {
    pub size: usize,
    pub black_player: Option<String>,
    pub white_player: Option<String>,
    pub date: Option<String>,
    pub moves: Vec<SgfMove>,
    pub result: Option<String>,
}

impl SgfGame {
    pub fn parse(input: &str) -> Result<Self, String> {
        let mut size = 9;
        let mut black_player = None;
        let mut white_player = None;
        let mut date = None;
        let mut result = None;
        let mut moves = Vec::new();

        let input = input.replace('\n', "").replace('\r', "");

        let mut chars = input.chars().peekable();

        while let Some(ch) = chars.next() {
            if ch.is_alphabetic() {
                let mut prop_name = String::new();
                prop_name.push(ch);

                while let Some(&c) = chars.peek() {
                    if c.is_alphabetic() {
                        prop_name.push(chars.next().unwrap());
                    }
                    else {
                        break;
                    }
                }

                if chars.peek() == Some(&'[') {
                    chars.next();
                    let mut value = String::new();
                    while let Some(c) = chars.next() {
                        if c == ']' {
                            break;
                        }
                        value.push(c);
                    }

                    match prop_name.as_str() {
                        "RE" => result = Some(value),
                        "PB" => black_player = Some(value),
                        "PW" => white_player = Some(value),
                        "SZ" => size = value.parse().unwrap_or(9),
                        "DT" => date = Some(value),
                        "B" => {
                            if let Some(pos) = Self::parse_sgf_coords(&value) {
                                moves.push(SgfMove::BlackMove(pos));
                            }
                        }
                        "W" => {
                            if let Some(pos) = Self::parse_sgf_coords(&value) {
                                moves.push(SgfMove::WhiteMove(pos));
                            }
                        }
                        _ => {}
                    }
                }
            }
        }

        Ok(SgfGame {
            size,
            black_player,
            white_player,
            date,
            result,
            moves,
        })
    }

    pub fn from_file(path: &str) -> Result<Self, String> {
        let content =
            std::fs::read_to_string(path).map_err(|e| format!("Failed to read file: {}", e))?;
        Self::parse(&content)
    }

    fn parse_sgf_coords(coords: &str) -> Option<Position> {
        if coords.len() != 2 {
            return None;
        }

        let chars: Vec<char> = coords.chars().collect();
        let col_char = chars[0];
        let row_char = chars[1];

        let col = (col_char as usize).wrapping_sub('a' as usize);
        let row = (row_char as usize).wrapping_sub('a' as usize);

        if col > 8 || row > 8 {
            return None;
        }
        Position::new(row, col)
    }
}