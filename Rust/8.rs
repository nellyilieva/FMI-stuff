use std::rc::Rc;

struct List<T> {
    head: Link<T>,
}

type Link<T> = Option<Rc<Node<T>>>;

struct Node<T> {
    elem: T,
    next: Link<T>,
}

impl<T> List<T> {
    pub fn new() -> Self {
        List { head: None }
    }

    pub fn head(&self) -> Option<&T> {
        self.head.as_ref().map(|node| &node.elem)
    }

    pub fn tail(&self) -> List<T> {
        List {
            head: self.head.as_ref().and_then(|node| node.next.clone()),
        }
    }

    pub fn prepend(&self, value: T) -> List<T> {
        List {
            head: Some(Rc::new(Node {
                elem: value,
                next: self.head.clone(),
            })),
        }
    }

    pub fn iter(&self) -> Iter<'_, T> {
        Iter {
            next: self.head.as_deref(),
        }
    }
}

pub struct Iter<'a, T> {
    next: Option<&'a Node<T>>,
}

impl<'a, T> Iterator for Iter<'a, T> {
    type Item = &'a T;

    fn next(&mut self) -> Option<Self::Item> {
        self.next.map(|node| {
            self.next = node.next.as_deref();
            &node.elem
        })
    }
}

//Когато имаме списък с голям брой елементи и опитаме да го изтрием с drop(),
//освобождаването на паметта става рекурсивно, структурата и всеки Node последователно.
//Всяко рекурсивно извикване заема място в стека => при много елементи -> stack overflow.
//Затова можем да направим custom, интеративна имплементация на drop.

impl<T> Drop for List<T> {
    fn drop(&mut self) {
        let mut head = self.head.take();
        while let Some(node) = head {
            if let Ok(mut node) = Rc::try_unwrap(node) {
                head = node.next.take();
            }
            else {
                break;
            }
        }
    }
}

fn main() {
    let mut list = List::new();
    for i in 0..1_000_000 {
        list = list.prepend(i);
    }
    std::mem::drop(list);
}