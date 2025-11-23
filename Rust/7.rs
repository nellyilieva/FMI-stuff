struct Map<I, F> {
    iter: I,
    f: F,
}

fn iter_map<I, F, U>(iter: I, f: F) -> Map<I, F>
where
    I: Iterator,
    F: Fn(I::Item) -> U
{
    Map {iter, f}
}

impl<I, F, U> Iterator for Map<I, F>
where
    I: Iterator,
    F: Fn(I::Item) -> U
{
    type Item = U;

    fn next(&mut self) -> Option<Self::Item> {
        match self.iter.next() {
            Some(item) => Some((self.f)(item)),
            None => None,
        }
    }
}

struct Filter<I, F> {
    iter: I,
    func: F,
}

fn iter_filter<I, F>(iter: I, func: F) -> Filter<I, F>
where
    I: Iterator,
    F: Fn(&I::Item) -> bool,
{
    Filter { iter, func }
}

impl<I, F> Iterator for Filter<I, F>
where
    I: Iterator,
    F: Fn(&I::Item) -> bool,
{
    type Item = I::Item;

    fn next(&mut self) -> Option<Self::Item> {
        while let Some(item) = self.iter.next() {
            if (self.func)(&item) {
                return Some(item)
            }
        }
        None
    }
}

fn iter_filter_map<I, F, U>(iter: I, func: F) -> impl Iterator<Item = U>
where
    I: Iterator,
    F: Fn(I::Item) -> Option<U>,
{
    iter_map(
        iter_filter(
            iter_map(iter, func), |opt|opt.is_some()
        ),
        |opt|opt.unwrap()
    )
}

//Изпозлваме impl Iterator, а не конкретния тип на резултата, защото типът би бил много сложен.
//Конкретният тип зависи от вложените адаптери; също така компилаторът генерира closure типът => става сложно.
//impl Iterator ни позволява да не казваме точно кой е типа, използваме нещо което връща итератор.

fn get_sum(text: &str) -> i32 {
    text.lines().map(|line| line.trim()).filter(|line| !line.is_empty())
    .filter_map(|line| line.parse::<i32>().ok()).sum()
}

#[derive(Debug, Eq, PartialEq)]
struct FoundWord<'a>(&'a str);

fn get_num_list(text: &str) -> Result<Vec<i32>, FoundWord<'_>> {
    text.lines().map(|line| line.trim()).filter(|line| !line.is_empty())
    .map(|line| {
        line.parse::<i32>().map_err(|_| FoundWord(line))
    }).collect()
}


fn main() {

}