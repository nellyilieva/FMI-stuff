use std::collections::HashMap;
use std::hash::Hash;

pub trait MyFromIterator<A> {
    fn my_from_iter<I>(iter: I) -> Self
    where
        I: Iterator<Item = A>;
}


impl<T> MyFromIterator<T> for Vec<T> {
    fn my_from_iter<I>(iter: I) -> Self
        where
            I: Iterator<Item = T>, {
        let mut vec = Vec::new();

        for i in iter {
            vec.push(i);
        }

        vec
    }
}

impl MyFromIterator<char> for String {
    fn my_from_iter<I>(iter: I) -> Self
        where
            I: Iterator<Item = char>, {
        let mut string = String::new();

        for ch in iter {
            string.push(ch);
        }

        string
    }
}

impl<K, V> MyFromIterator<(K, V)> for HashMap<K, V>
where
    K: Eq + Hash, {

    fn my_from_iter<I>(iter: I) -> Self
        where
            I: Iterator<Item = (K, V)>, {
        let mut map = HashMap::new();

        for (key, value) in iter {
            map.insert(key, value);
        }

        map
    }
}

fn my_collect<I, C>(iter: I) -> C
where
    I: Iterator,
    C: MyFromIterator<I::Item>, {
    C::my_from_iter(iter)
}

fn main() {
    let bytes: Vec<u8> = my_collect("hello".bytes());
    let chars: Vec<char> = my_collect("hello".chars());
    let index_to_char: HashMap<usize, char> = my_collect("hello".char_indices());
    let digits: String = my_collect("1a2b3c4d".chars().filter(|c| c.is_ascii_digit()));

    println!("{bytes:?}");
    println!("{chars:?}");
    println!("{index_to_char:?}");
    println!("{digits:?}");
}