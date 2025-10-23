// fn calc(a: i32, b: i32, op: char) -> i32 {
//     if op == '+' {
//         a + b
//     }
//     else if op == '-' {
//         a - b
//     }
//     else if op == '*' {
//         a * b
//     }
//     else if op == '/' && b != 0 {
//         a/b
//     }
//     else if op == '/' && b == 0 {
//         0
//     }
//     else {
//         42
//     }
// }

// fn check_triangle(a: i32, b: i32, c: i32) -> &'static str{
//     if a <= 0 || b <= 0 || c <= 0 {
//         "невалидни страни"
//     }
//     else if a + b < c || a + c < b || b + c < a {
//         "не е триъгълник"
//     }
//     else if a == b && b == c {
//         "равностранен"
//     }
//     else if (a == b && a != c) || (a == c && a != b) || (b == c && b != a) {
//         "равнобедрен"
//     }
//     else {
//         "разностранен"
//     }
// }

// fn check_password(pass: &str) -> bool {
//     if pass.len() < 8 {
//         return false
//     }

//     //pass as bytes() -> &[u8]

//     let first = pass.chars().next().unwrap();
//     let last = pass.chars().last().unwrap();

//     if !first.is_uppercase() || !last.is_numeric() {
//         return false
//     }

//     true
// }

// #[derive(Debug)]
// struct User {
//     name: String, // not Copy
//     age: u32,     // Copy, but struct as a whole is not
// }


// #[derive(Debug)]
// struct Point {
//     x: String,
//     y: String,
// }

// #[derive(Debug)]
// struct User { name: String, age: u32 }

// fn print_user(user: &User) {
//     println!("{:?}", user);
// }

// fn increment_age(user: &mut User) {
//     user.age += 1;
// }


// fn main() {
//      let user = User {
//         name: "Alice".to_string(),
//         age: 30,
//     };

//     println!("{:?}", user);
// }


// std::io
// use std::io::{self, Read}

// fn main() {
//     let mut name = String::new();
//     io::stdin().read_line(&mut name).expect("error");
// }


fn duplicate_i32(x: i32) -> (i32, i32) {
    // let x1 = x;
    // (x1, x)
    (x, x)
}

fn duplicate_string(s: String) -> (String, String) {
    let s1 = s.clone();
    (s1, s)
}

//b
//i32 имплементира копиране (Copy). Т.е когато x е във функцията, стойността се копира, а не се move-ва.
//Затова можем да го използваме след функцията.
//String не имплементира Copy и когато влезем във функцията, оригиналният стринг вече не е валиден.
//За да можем да използваме s 2 пъти трябва да използваме .clone().

//c
//Не можем да копираме String без .clone().
//Ако използваме (s, s), ще се опитаме да move-нем s 2 пъти,
//един път на първата стойност на tuple-a и още един път на втората стойност, но s вече не е валидно.

fn print_str(s: &str) {
    println!("Стрингово съдържание: {}", s);
}

fn append_exclamation(s: &mut String) {
    s.push('!');
}

//b
//Използваме &str, защото искаме само да прочетем стойността, не я създаваме и е част от входните данни.

//c
//Използваме &mut String, защото при него можем да променяме оригиналния стринг,
//докато при &mut str не можем да махаме или добавяме символи.

//d
//(Readers and writers)
//Няма да се компилира, защото не може да имаме едновремено mutable и immutable референция към един обект.
//Не можем да четем и пишеш едновремено, може да стане race condition.

fn split_string_at(s: String, n: usize) -> (String, String) {
    let first = s[..n].to_string();
    let second = s[n..].to_string();
    (first, second)
}

//Функцията връща 2 нови стринга. Те не зависят от s, защото всеки има собствена памет.
//Нямаме проблем с ownership-a.
//Тук s ще бъде изтрит след приключване на функцията; не можем да върнем &str, защото ще сочи към нещо,
//което го няма => няма да се компилира кодът.

fn split_slice_at(s: &str, n: usize) -> (&str, &str) {
    let first = &s[..n];
    let second = &s[n..];
    (first, second) 

}

//Тук s е референция към някакъв стринг. Връщаме 2 референции към този стринг.
//Връщаме част от стринга, която мойем само да прочетем.
//Ако искаме да върнем String, ще трябва да направим копие с .to_string().

// fn split_slice_mut_at(s: &mut str, n: usize) -> (&mut str, &mut str) {
//     let first = &mut s[..n];
//     let second = &mut s[n..];
//     (first, second)
// }

//Няма да се компилира. Не е позволено да имаме 2 mutable референции, защото не е гарантирано,
//че няма да се припокриват.

fn split_slice_mut_at(s: &mut str, n: usize) -> (&mut str, &mut str) {
    s.split_at_mut(n)
}



fn sum_slice(arr: &[i32]) -> i32 {
    let mut sum = 0;

    for n in arr {
        sum += n;
    }

    sum
}

//b
//&v автоматично се превръща в &[i32]. Това е slice от вектора.

//c
//a[2] е число от тип i32, &a[2] е &i32, а функцията очаква &[i32].
//Типовете не съвпадат, затова няма да се компилира.


//Функциите приемат Vec<i32>, а в main-a им се подава &mut Vec<i32>.
//fill_vec трябва да приеме вектор, да го промени и не трябва да връща нищо
//filled_vec трябва да приеме вектор, да промени собствеността и да върне новия вектор с добавена стойност

fn fill_vec(vec: &mut Vec<i32>, num: i32) {
    vec.push(num);
}
fn filled_vec(mut vec: Vec<i32>, num: i32) -> Vec<i32> {
    vec.push(num);
    vec
}

fn main() {
    let mut vec1 = vec![22, 44];
    fill_vec(&mut vec1, 66);
    fill_vec(&mut vec1, 88);
    assert_eq!(vec1, vec![22, 44, 66, 88]);

    let vec2 = filled_vec(filled_vec(vec![22, 44], 66), 88);
    assert_eq!(vec2, vec![22, 44, 66, 88]);
}