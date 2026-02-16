use crossterm::{
    cursor::{self, Hide, Show},
    style::{Color, Print, SetForegroundColor, SetBackgroundColor, ResetColor},
    terminal::{self, ClearType},
    ExecutableCommand, //trait that lets you send commands to the terminal, using execute()
};

use std::io::{stdout, Write};

use crate::types::{Board, Stone, Position};

pub struct BoardDisplay;
impl BoardDisplay {
    pub fn draw(board: &Board) -> std::io::Result<()> {
        let mut stdout = stdout();
        
        stdout.execute(terminal::Clear(ClearType::All))?;
        stdout.execute(cursor::Hide)?;
        
        Self::draw_grid(&mut stdout)?;
        Self::draw_stones(&mut stdout, board)?;
        Self::draw_coordinates(&mut stdout)?;
        
        stdout.execute(cursor::MoveTo(0, 15))?;
        stdout.execute(cursor::Show)?;
        stdout.flush()?;
        
        Ok(())
    }
    
    fn draw_grid(stdout: &mut impl Write) -> std::io::Result<()> {
        let start_row = 2;
        let start_col = 4;
        
        for row in 0..9 {
            for col in 0..9 {
                let screen_row = start_row + row as u16;
                let screen_col = start_col + (col as u16 * 2);
                
                stdout.execute(cursor::MoveTo(screen_col, screen_row))?;
                
                let symbol = match (row, col) {
                    (0, 0) => "┌",
                    (0, 8) => "┐",
                    (8, 0) => "└",
                    (8, 8) => "┘",
                    (0, _) => "┬",
                    (8, _) => "┴",
                    (_, 0) => "├",
                    (_, 8) => "┤",
                    _ => "┼",
                };
                
                stdout.execute(SetForegroundColor(Color::DarkGrey))?;
                stdout.execute(Print(symbol))?;
            }
        }
        
        stdout.execute(ResetColor)?;
        Ok(())
    }

    fn draw_stones(stdout: &mut impl Write, board: &Board) -> std::io::Result<()> {
        let start_row = 2;
        let start_col = 4;
        
        for row in 0..9 {
            for col in 0..9 {
                if let Some(pos) = Position::new(row, col) {
                    if let Some(stone) = board.get(pos) {
                        let screen_row = start_row + row as u16;
                        let screen_col = start_col + (col as u16 * 2);
                        
                        stdout.execute(cursor::MoveTo(screen_col, screen_row))?;
                        
                        match stone {
                            Stone::Black => {
                                //stdout.execute(SetForegroundColor(Color::DarkGrey))?;
                                stdout.execute(SetForegroundColor(Color::Blue))?;
                                stdout.execute(Print("●"))?;
                            }
                            Stone::White => {
                                stdout.execute(SetForegroundColor(Color::White))?;
                                //stdout.execute(SetForegroundColor(Color::Black))?;
                                stdout.execute(Print("●"))?;
                            }
                        }
                    }
                }
            }
        }
        
        Ok(())
    }

    fn draw_coordinates(stdout: &mut impl Write) -> std::io::Result<()> {
        let start_row = 2;
        let start_col = 4;
        
        let letters = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J'];
        
        for (i, letter) in letters.iter().enumerate() {
            stdout.execute(cursor::MoveTo(start_col + (i as u16 * 2), start_row - 1))?;
            stdout.execute(SetForegroundColor(Color::Yellow))?;
            stdout.execute(Print(letter))?;
        }
        stdout.execute(Print("\n"))?;
        
        for i in 0..9 {
            stdout.execute(cursor::MoveTo(0, start_row + i as u16))?;
            stdout.execute(SetForegroundColor(Color::Yellow))?;
            stdout.execute(Print(format!("{} ", 9 - i)))?;
        }
        
        stdout.execute(ResetColor)?;
        Ok(())
    }
    
    pub fn show_message(msg: &str) -> std::io::Result<()> {
        let mut stdout = stdout();
        stdout.execute(cursor::MoveTo(0, 13))?;
        stdout.execute(SetForegroundColor(Color::Cyan))?;
        stdout.execute(Print(msg))?;
        stdout.execute(ResetColor)?;
        stdout.flush()?;
        Ok(())
    }
}