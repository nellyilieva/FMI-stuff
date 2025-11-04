#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum CompareResult {
    Less,
    Equal,
    Greater,
}

trait Compare {
    fn compare(&self, other: &Self) -> CompareResult;
}

trait Filter {
    fn matches(&self, query: &str) -> bool;
}

trait Aggregate {
    type Output;
    fn aggregate(items: &[Self]) -> Self::Output
    where
        Self: Sized;
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum SortOrder {
    Desc,
    Asc,
}

fn process_items<T>(items: Vec<T>, query: &str, order: SortOrder) -> (Vec<T>, T::Output)
where
    T: Compare + Filter + Aggregate + Clone, {
    
    let mut filtered: Vec<T> = items.into_iter().filter(|item| item.matches(query)).collect();

    for i in 1..filtered.len() {
        let mut j = i;
        while j > 0 {
            let cmp = filtered[j].compare(&filtered[j - 1]);
            let should_swap = match order {
                SortOrder::Asc => matches!(cmp, CompareResult::Less),
                SortOrder::Desc => matches!(cmp, CompareResult::Greater),
            };

            if should_swap {
                filtered.swap(j, j - 1);
            }
            else {
                break;
            }
            j -= 1;
        }
    }

    let aggregate = T::aggregate(&filtered);

    (filtered, aggregate)
}

#[derive(Clone)]
struct Book {
    title: String,
    author: String,
    year: u32,
    rating: f32,
}

impl Filter for Book {
    fn matches(&self, query: &str) -> bool {
        self.title.contains(query) || self.author.contains(query)
    }
}

impl Compare for Book {
    fn compare(&self, other: &Self) -> CompareResult {
        if self.year < other.year {
            CompareResult::Less
        }
        else if self.year > other.year {
            CompareResult::Greater
        }
        else {
            CompareResult::Equal
        }
    }
}

impl Aggregate for Book {
    type Output = f32;

    fn aggregate(items: &[Self]) -> Self::Output {
        if items.is_empty() {
            0.0
        }
        else {
            let sum: f32 = items.iter().map(|b| b.rating).sum();
            sum / (items.len() as f32)
        }
    }
}

fn main() {
    let books = vec![
        Book { title: "The Rust Book".into(), author: "Steve".into(), year: 2018, rating: 4.7 },
        Book { title: "Rust Patterns".into(), author: "Anna".into(), year: 2020, rating: 4.9 },
        Book { title: "C Programming".into(), author: "Dennis".into(), year: 1978, rating: 4.3 },
    ];

    let (result, avg_rating) = process_items(books, "Rust", SortOrder::Asc);
    println!("Filtered & sorted:");
    for b in &result {
        println!("{} by {} ({})", b.title, b.author, b.year);
    }
    println!("Average rating: {:.2}", avg_rating);
}