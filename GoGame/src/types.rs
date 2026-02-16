use std::collections::{HashMap, HashSet};
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Stone {
    Black,
    White,
}

impl Stone {
    pub fn opponent(&self) -> Stone {
        match self {
            Stone::Black => Stone::White,
            Stone::White => Stone::Black,
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub struct Position {
    pub row: usize,
    pub col: usize,
}

impl Position {
    pub fn new(row: usize, col: usize) -> Option<Self> {
        if row < 9 && col < 9 {
            Some(Position { row, col })
        }
        else {
            None
        }
    }

    pub fn neighbors(&self) -> Vec<Position> {
        let mut result = Vec::new();

        if self.row > 0 {
            result.push(Position {
                row: self.row - 1,
                col: self.col,
            });
        }

        if self.row < 8 {
            result.push(Position {
                row: self.row + 1,
                col: self.col,
            });
        }

        if self.col > 0 {
            result.push(Position {
                row: self.row,
                col: self.col - 1,
            });
        }

        if self.col < 8 {
            result.push(Position {
                row: self.row,
                col: self.col + 1,
            });
        }

        result
    }

    pub fn from_notation(s: &str) -> Option<Self> {
        let s = s.trim().to_uppercase();
        if s.len() < 2 {
            return None;
        }

        let mut chars = s.chars();
        let col_char = chars.next()?;
        let row_str: String = chars.collect();

        let col = match col_char {
            'A' => 0,
            'B' => 1,
            'C' => 2,
            'D' => 3,
            'E' => 4,
            'F' => 5,
            'G' => 6,
            'H' => 7,
            'J' => 8,
            _ => return None,
        };

        let row_num: usize = row_str.parse().ok()?;
        if row_num < 1 || row_num > 9 {
            return None;
        }

        let row = 9 - row_num;

        Some(Position { row, col })
    }

    pub fn to_notation(&self) -> String {
        let letters = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J'];
        let col_char = letters[self.col];
        let row_num = 9 - self.row;
        format!("{}{}", col_char, row_num)
    }
}

#[derive(Debug, Clone, PartialEq, Eq)]
pub struct Board {
    grid: [[Option<Stone>; 9]; 9],
}

impl Board {
    pub fn new() -> Self {
        Board {
            grid: [[None; 9]; 9],
        }
    }

    pub fn place_stone(&mut self, pos: Position, stone: Stone) -> Result<(), String> {
        if self.grid[pos.row][pos.col].is_some() {
            return Err("The position is not free".to_string());
        }

        self.grid[pos.row][pos.col] = Some(stone);
        Ok(())
    }

    pub fn get(&self, pos: Position) -> Option<Stone> {
        self.grid[pos.row][pos.col]
    }

    pub fn remove_stone(&mut self, pos: Position) {
        self.grid[pos.row][pos.col] = None;
    }

    pub fn is_empty(&self, pos: Position) -> bool {
        self.grid[pos.row][pos.col].is_none()
    }

    //LIBERTIES

    pub fn find_group(&self, start: Position) -> HashMap<Position, Stone> {
        let mut group = HashMap::new();

        let Some(stone_color) = self.get(start)
        else {
            return group;
        };

        let mut to_check = vec![start];

        while let Some(pos) = to_check.pop() {
            if group.contains_key(&pos) {
                continue;
            }

            group.insert(pos, stone_color);

            for neighbor in pos.neighbors() {
                if self.get(neighbor) == Some(stone_color) && !group.contains_key(&neighbor) {
                    to_check.push(neighbor);
                }
            }
        }

        group
    }

    pub fn count_liberties(&self, group: &HashMap<Position, Stone>) -> usize {
        let mut liberties = HashSet::new();
        for &pos in group.keys() {
            for neighbor in pos.neighbors() {
                if self.is_empty(neighbor) {
                    liberties.insert(neighbor);
                }
            }
        }

        liberties.len()
    }

    pub fn is_captured(&self, group: &HashMap<Position, Stone>) -> bool {
        self.count_liberties(group) == 0
    }

    pub fn get_liberties(&self, group: &HashMap<Position, Stone>) -> HashSet<Position> {
        let mut liberties = HashSet::new();

        for &pos in group.keys() {
            for neighbor in pos.neighbors() {
                if self.is_empty(neighbor) {
                    liberties.insert(neighbor);
                }
            }
        }

        liberties
    }

    //SUICIDE RULE

    pub fn is_suicide(&self, pos: Position, stone: Stone) -> bool {
        let mut temp_board = self.clone();

        temp_board.grid[pos.row][pos.col] = Some(stone);

        let group = temp_board.find_group(pos);

        if temp_board.count_liberties(&group) > 0 {
            return false;
        }

        for neighbor in pos.neighbors() {
            if let Some(neighbor_stone) = temp_board.get(neighbor) {
                if neighbor_stone == stone.opponent() {
                    let neighbor_group = temp_board.find_group(neighbor);
                    if temp_board.is_captured(&neighbor_group) {
                        return false;
                    }
                }
            }
        }
        true
    }

    pub fn is_legal_move(&self, pos: Position, stone: Stone) -> Result<(), String> {
        if !self.is_empty(pos) {
            return Err("Position is already occupied".to_string());
        }

        let mut temp_board = self.clone();
        temp_board.grid[pos.row][pos.col] = Some(stone);

        temp_board.remove_captured_stones(pos, stone);

        let group = temp_board.find_group(pos);

        if temp_board.count_liberties(&group) == 0 {
            return Err("Suicide move is not allowed".to_string());
        }

        Ok(())
    }

    //CAPTURING

    pub fn remove_captured_stones(&mut self, last_move: Position, stone: Stone) -> usize {
        let mut captured_count = 0;
        let opponent = stone.opponent();

        for neighbor in last_move.neighbors() {
            if self.get(neighbor) == Some(opponent) {
                let group = self.find_group(neighbor);

                if self.is_captured(&group) {
                    for pos in group.keys() {
                        self.remove_stone(*pos);
                        captured_count += 1;
                    }
                }
            }
        }
        captured_count
    }

    pub fn make_move(&mut self, pos: Position, stone: Stone) -> Result<usize, String> {
        if !self.is_empty(pos) {
            return Err("Position is already occupied".to_string());
        }

        self.grid[pos.row][pos.col] = Some(stone);

        let captured = self.remove_captured_stones(pos, stone);

        let group = self.find_group(pos);
        if self.count_liberties(&group) == 0 {
            self.remove_stone(pos);
            return Err("Suicide move is not allowed".to_string());
        }

        Ok(captured)
    }

    //Ko Rule

    pub fn position_hash(&self) -> String {
        let mut hash = String::new();
        for row in 0..9 {
            for col in 0..9 {
                let pos = Position::new(row, col).unwrap();
                match self.get(pos) {
                    Some(Stone::Black) => hash.push('B'),
                    Some(Stone::White) => hash.push('W'),
                    None => hash.push('.'),
                }
            }
        }
        hash
    }

    pub fn violates_ko(
        &self,
        pos: Position,
        stone: Stone,
        previous_board_state: Option<&Board>,
    ) -> bool {
        let Some(prev_board) = previous_board_state else {
            return false;
        };

        let mut temp_board = self.clone();
        if temp_board.place_stone(pos, stone).is_err() {
            return false;
        }

        temp_board.remove_captured_stones(pos, stone);

        temp_board == *prev_board
    }
}

impl Default for Board {
    fn default() -> Self {
        Self::new()
    }
}