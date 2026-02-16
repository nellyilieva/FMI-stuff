use crate::types::{Board, Position, Stone};

#[derive(Debug, Clone)]
pub struct Game {
    pub board: Board,
    pub current_player: Stone,
    pub previous_board: Option<Board>,
    pub move_history: Vec<(Position, Stone)>,
    pub captured_stones: (usize, usize), 
    pub consecutive_passes: usize,
    pub komi: f32,
}

impl Game {
    pub fn new() -> Self {
        Game {
            board: Board::new(),
            current_player: Stone::Black,
            previous_board: None,
            move_history: Vec::new(),
            captured_stones: (0, 0),
            consecutive_passes: 0,
            komi: 6.5,
        }
    }

    pub fn make_move(&mut self, pos: Position) -> Result<usize, String> {
        let stone = self.current_player;
        self.board.is_legal_move(pos, stone)?;

        if self.board.violates_ko(pos, stone, self.previous_board.as_ref()) {
            return Err("Ko rule violation: cannot immediately recapture".to_string());
        }

        let board_before_move = self.board.clone();
        let captured = self.board.make_move(pos, stone)?;

        match stone {
            Stone::Black => self.captured_stones.0 += captured,
            Stone::White => self.captured_stones.1 += captured,
        }

        self.move_history.push((pos, stone));
        self.previous_board = Some(board_before_move);
        self.current_player = self.current_player.opponent();
        self.consecutive_passes = 0;

        Ok(captured)
    }

    pub fn pass(&mut self) {
        self.current_player = self.current_player.opponent();
        self.consecutive_passes += 1;
    }

    pub fn is_game_over(&self) -> bool {
        self.consecutive_passes >= 2
    }

    pub fn whose_turn(&self) -> Stone {
        self.current_player
    }

    pub fn calculate_score(&self) -> (f32, f32) {
        let mut black_points = 0;
        let mut white_points = 0;
        let mut visited = [[false; 9]; 9];

        for r in 0..9 {
            for c in 0..9 {
                let pos = Position { row: r, col: c };
                match self.board.get(pos) {
                    Some(Stone::Black) => black_points += 1,
                    Some(Stone::White) => white_points += 1,
                    None => {}
                }
            }
        }

        for row in 0..9 {
            for col in 0..9 {
                let pos = Position { row, col };
                if !visited[row][col] && self.board.is_empty(pos) {
                    let (size, owner) = Game::find_territory_on(&self.board, pos, &mut visited);
                    match owner {
                        Some(Stone::Black) => black_points += size,
                        Some(Stone::White) => white_points += size,
                        None => {} 
                    }
                }
            }
        }

        (black_points as f32, white_points as f32 + self.komi)
    }

    fn find_territory_on(board: &Board, start: Position, visited: &mut [[bool; 9]; 9]) -> (usize, Option<Stone>) {
        let mut territory_size = 0;
        let mut neighbors = vec![start];
        let mut black_seen = false;
        let mut white_seen = false;
        let mut region = Vec::new();

        while let Some(pos) = neighbors.pop() {
            if visited[pos.row][pos.col] { continue; }
            visited[pos.row][pos.col] = true;
            
            if board.is_empty(pos) {
                territory_size += 1;
                region.push(pos);
                for n in pos.neighbors() {
                    neighbors.push(n);
                }
            }
            else {
                match board.get(pos) {
                    Some(Stone::Black) => black_seen = true,
                    Some(Stone::White) => white_seen = true,
                    None => {}
                }
            }
        }

        let owner = match (black_seen, white_seen) {
            (true, false) => Some(Stone::Black),
            (false, true) => Some(Stone::White),
            _ => None, 
        };

        (territory_size, owner)
    }

    pub fn format_result(&self, sgf_official_result: Option<&String>) -> String {
        let (black_score, white_score) = self.calculate_score();
        let mut output = format!(
            "\n=== ТЕКУЩА СТАТИСТИКА (от дъската) ===\n\
             Черни: {:.1} | Бели: {:.1} (вкл. {:.1} коми)\n",
            black_score, white_score, self.komi
        );

        if let Some(official_raw) = sgf_official_result {
            let official = official_raw.trim();
            output.push_str("\n=== ОФИЦИАЛЕН ПОБЕДИТЕЛ (от SGF) ===\n");
            let winner = if official.starts_with('B') { "ЧЕРНИТЕ (Black)" } else { "БЕЛИТЕ (White)" };
            let detail = if official.contains("+R") { "ПРЕДАВАНЕ (Resignation)" } else { "ТОЧКИ" };
            
            output.push_str(&format!(">>> {} ПЕЧЕЛЯТ!\n>>> Основание: {}\n>>> Код: {}\n", winner, detail, official));
        }
        else {
            let winner = if black_score > white_score { "Черните" } else { "Белите" };
            output.push_str(&format!("\nКРАЕН РЕЗУЛТАТ: {} печелят с {:.1} точки!", winner, (black_score - white_score).abs()));
        }
        output
    }
}

impl Default for Game {
    fn default() -> Self { Self::new() }
}