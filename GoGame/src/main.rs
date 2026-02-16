mod display;
mod game;
mod sgf;
mod types;

use display::BoardDisplay;
use game::Game;
use sgf::{SgfGame, SgfMove};
use std::fs;
use std::io::{self, Write};
use types::{Position};

fn main() {
    println!("=== GO GAME (9x9) ===\n");
    println!("Изберете режим:");
    println!("  1. Игра");
    println!("  2. Преглед на SGF запис");
    println!("  3. Изход");
    println!("  4. Help");
    print!("\nВашият избор: ");
    io::stdout().flush().ok();

    let mut choice = String::new();
    io::stdin().read_line(&mut choice).ok();

    match choice.trim() {
        "1" => play_interactive(),
        "2" => replay_sgf(),
        "3" => println!("Довиждане!"),
        "4" => show_help(),
        _ => println!("Невалиден избор"),
    }
}

fn play_interactive() {
    println!("\n=== ИГРА ===");
    println!("Команди: D4, E5... | 'pass' | 'resign' | 'quit'\n");

    let mut game = Game::new();
    let mut status = String::new();

    loop {
        BoardDisplay::draw(&game.board).ok();
        println!("\nХод на: {:?}", game.whose_turn());
        println!("Пленници - Черни: {}, Бели: {}", game.captured_stones.0, game.captured_stones.1);

        if !status.is_empty() {
            println!("{}", status);
            status.clear();
        }

        if game.is_game_over() {
            println!("{}", game.format_result(None));
            break;
        }

        print!("\nВъведете ход: ");
        io::stdout().flush().ok();

        let mut input = String::new();
        io::stdin().read_line(&mut input).ok();
        let input = input.trim().to_lowercase();

        match input.as_str() {
            "quit" => break,
            "pass" => {
                game.pass();
                status = format!("✓ {:?} пасува.", game.whose_turn().opponent());
            }
            "resign" => {
                println!("\n{:?} се предаде! Победа за {:?}", game.whose_turn(), game.whose_turn().opponent());
                break;
            }
            _ => {
                if let Some(pos) = Position::from_notation(&input) {
                    if let Err(e) = game.make_move(pos) {
                        println!("✗ {}", e);
                        io::stdin().read_line(&mut String::new()).ok();
                    }
                } else {
                    println!("✗ Невалидна нотация");
                }
            }
        }
    }
}

fn replay_sgf() {
    let sgf_dir = "sgf_games";
    let Ok(entries) = fs::read_dir(sgf_dir) else {
        println!("✗ Папката '{}' не е намерена!", sgf_dir);
        return;
    };

    let sgf_files: Vec<_> = entries
        .filter_map(|e| e.ok())
        .map(|e| e.path())
        .filter(|p| p.extension().and_then(|s| s.to_str()) == Some("sgf"))
        .collect();

    if sgf_files.is_empty() {
        println!("✗ Няма намерени .sgf файлове.");
        return;
    }

    println!("\nНалични игри:");
    for (i, path) in sgf_files.iter().enumerate() {
        println!("  {}. {}", i + 1, path.file_name().unwrap().to_str().unwrap());
    }

    print!("\nИзберете файл (1-{}): ", sgf_files.len());
    io::stdout().flush().ok();
    let mut choice = String::new();
    io::stdin().read_line(&mut choice).ok();

    let Ok(idx) = choice.trim().parse::<usize>().map(|n| n.wrapping_sub(1)) else { return; };
    if idx >= sgf_files.len() { return; }

    let sgf_game = SgfGame::from_file(sgf_files[idx].to_str().unwrap()).expect("Грешка при зареждане");
    
    println!("\n✓ Заредено: Black: {:?} vs White: {:?} | Резултат: {:?}", 
             sgf_game.black_player, sgf_game.white_player, sgf_game.result);

    let mut game = Game::new();
    let mut current_move = 0;

    loop {
        BoardDisplay::draw(&game.board).ok();
        println!("\nХод: {}/{}", current_move, sgf_game.moves.len());
        println!("Пленници - Черни: {}, Бели: {}", game.captured_stones.1, game.captured_stones.0);

        if current_move < sgf_game.moves.len() {
            let next = &sgf_game.moves[current_move];
            match next {
                SgfMove::BlackMove(p) => println!("Следва: Черен на {}", p.to_notation()),
                SgfMove::WhiteMove(p) => println!("Следва: Бял на {}", p.to_notation()),
            }
        } else {
            println!("\nКРАЙ НА ЗАПИСА!");
            println!("{}", game.format_result(sgf_game.result.as_ref()));
        }

        print!("\nКоманда (n=напред, p=назад, q=изход): ");
        io::stdout().flush().ok();
        let mut cmd = String::new();
        io::stdin().read_line(&mut cmd).ok();

        match cmd.trim().to_lowercase().as_str() {
            "q" | "quit" => {
                println!("{}", game.format_result(sgf_game.result.as_ref()));
                break;
            }
            "n" | "next" => {
                if current_move < sgf_game.moves.len() {
                    let m = &sgf_game.moves[current_move];
                    let pos = match m { SgfMove::BlackMove(p) | SgfMove::WhiteMove(p) => *p };
                    if game.make_move(pos).is_ok() { current_move += 1; }
                }
            }
            "p" | "prev" => {
                if current_move > 0 {
                    current_move -= 1;
                    game = Game::new();
                    // Преиграваме до текущия ход
                    for m in sgf_game.moves.iter().take(current_move) {
                        let pos = match m { SgfMove::BlackMove(p) | SgfMove::WhiteMove(p) => *p };
                        let _ = game.make_move(pos);
                    }
                }
            }
            _ => {}
        }
    }
}

fn show_help() {
    println!("\n========= GO GAME HELP =========\n");
    
    println!("--- 1.ИГРА (Play) ---");
    println!("* Позиция: Пиши координати (напр. 'D4', 'E5', 'C3').");
    println!("* pass: Пропускаш ход. Ако и двамата пасуват -> край.");
    println!("* resign: Предаваш се веднага.");
    println!("* quit: Излизаш от играта.\n");

    println!("--- 2. ПРЕГЛЕД НА ЗАПИС (Replay) ---");
    println!("* n (next): Следващ ход от SGF файла.");
    println!("* p (prev): Връщаш един ход назад.");
    println!("* q (quit): Спираш прегледа и виждаш резултата.\n");

    println!("--- 3. БРОЕНЕ НА ТОЧКИ (Scoring) ---");
    println!("* Area Scoring: Броим територията + камъните на дъската.");
    println!("* Komi (6.5): Бонус точки за Белите (White).");
    println!("* Официален Резултат: Прочита се от RE[...] тага в SGF.\n");

    println!("====================================");
    print!("Натиснете Enter, за да се върнете...");
    io::stdout().flush().ok();
    io::stdin().read_line(&mut String::new()).ok();
}