//1
fn rainbow_replace(text: &str, word: &str, palette: &[char]) -> String {
    if text.len() == 0 || word.len() == 0 || palette.len() == 0 {
        return text.to_string();
    }

    let mut res = String::new();
    let mut chars = text.chars();
    
    while let Some(current_char) = chars.next() {
        let first_word_char = match word.chars().next() {
            Some(c) => c,
            None => {
                res.push(current_char);
                continue;
            }
        };
        
        let mut matches = current_char == first_word_char;
        let mut temp_chars = chars.clone();
        let mut word_iter = word.chars();
        
        word_iter.next();
        
        for expected_char in word_iter {
            if let Some(next_char) = temp_chars.next() {
                if next_char != expected_char {
                    matches = false;
                    break;
                }
            }
            else {
                matches = false;
                break;
            }
        }

        if matches {
            for (i, _) in word.chars().enumerate() {
                res.push(palette[i % palette.len()]);
            }
            for _ in 0..word.chars().count() - 1 {
                chars.next();
            }
        }
        else {
            res.push(current_char);
        }
    }
    
    res
}


//2
#[derive(Debug, Clone, Copy)]
enum VehicleKind {
    Car,
    Truck,
    Motorcycle,
    Bicycle,
}

struct Vehicle {
    kind: VehicleKind,
    fuel: f64,
    distance: f64,
}

#[derive(Debug)]
enum DriveError {
  NotEnoughFuel { needed: f64, have: f64 }
}

impl Vehicle {
    fn new(kind: VehicleKind, fuel: f64) -> Self {
        Vehicle {
            kind,
            fuel,
            distance: 0.0,
        }
    }

    fn drive(&mut self, km: f64) -> Result<(), DriveError> {

        let fuel_consump_km = match self.kind {
                VehicleKind::Car => 0.07,
                VehicleKind::Truck => 0.15,
                VehicleKind::Motorcycle => 0.05,
                VehicleKind::Bicycle => 0.0,
        };

        let fuel_need = fuel_consump_km * km;

        if fuel_need > self.fuel {
                return Err(DriveError::NotEnoughFuel { needed: fuel_need, have: self.fuel, });
        }
        
        self.fuel -= fuel_need;
        self.distance += km;
        
        Ok(())
    }
}

//3
use std::collections::HashMap;

#[derive(Debug, Clone)]
enum Event {
    Login { user: String, timestamp: u64 },
    Logout { user: String, timestamp: u64 },
    Purchase { user: String, item: String, amount: f64, timestamp: u64 },
    Error { code: i32, message: String, timestamp: u64 },
}

struct EventLog {
    events: Vec<Event>,
}

impl EventLog {
    fn new() -> Self {
        EventLog {
            events: Vec::new(),
        }
    }

    fn add_event(&mut self, event: Event) {
        self.events.push(event);
    }

    fn user_spent(&self, user: &str) -> f64 {
        self.events.iter().filter_map(|event| {
            match event {
                Event::Purchase { user: purchase_user, amount, .. } 
                    if purchase_user == user => Some(*amount),
                _ => None,
            }
        }).sum()
    }

    fn summaries_by_type(&self) -> HashMap<String, usize> {
        let mut summary = HashMap::new();
        
        for event in &self.events {
            let event_type = match event {
                Event::Login { .. } => "Login",
                Event::Logout { .. } => "Logout",
                Event::Purchase { .. } => "Purchase",
                Event::Error { .. } => "Error",
            }.to_string();
            
            *summary.entry(event_type).or_insert(0) += 1;
        }
        
        summary
    }

    fn filter_events(&self, user: Option<&str>, after: Option<u64>) -> Vec<&Event> {
        self.events.iter().filter(|event| {
            let user_match = match user {
                Some(username) => {
                    match event {
                        Event::Login { user, .. } => user == username,
                        Event::Logout { user, .. } => user == username,
                        Event::Purchase { user: purchase_user, .. } => purchase_user == username,
                        Event::Error { .. } => false,
                    }
                }
                None => true,
            };
                
            let time_match = match after {
                Some(min_timestamp) => {
                    let event_timestamp = match event {
                        Event::Login { timestamp, .. } => timestamp,
                        Event::Logout { timestamp, .. } => timestamp,
                        Event::Purchase { timestamp, .. } => timestamp,
                        Event::Error { timestamp, .. } => timestamp,
                    };
                    event_timestamp > &min_timestamp
                }
                None => true,
            };
            user_match && time_match
        }).collect()
    }
}


fn main() {

}