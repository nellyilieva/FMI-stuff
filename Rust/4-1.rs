#[derive(Debug, Clone)]
enum Spec {
    SI,
    IS,
    KN,
    I,
    M,
}

#[derive(Debug, Clone)]
enum Title {
    Assistant,
    Doctor,
    Professor,
}

trait ToJson: std::fmt::Debug {
    fn to_json(&self) -> String;
}

impl ToJson for Spec {
    fn to_json(&self) -> String {
        match self {
            Spec::SI => "\"SI\"".to_string(),
            Spec::IS => "\"IS\"".to_string(),
            Spec::KN => "\"KN\"".to_string(),
            Spec::I => "\"I\"".to_string(),
            Spec::M => "\"M\"".to_string(),
        }
    }
}

impl ToJson for Title {
    fn to_json(&self) -> String {
        match self {
            Title::Assistant => "\"Assistant\"".to_string(),
            Title::Doctor => "\"Doctor\"".to_string(),
            Title::Professor => "\"Professor\"".to_string(),
        }
    }
}

#[derive(Debug, Clone)]
struct Student {
    name: String,
    age: u32,
    spec: Spec,
}

impl Student {
    fn new(name: String, age: u32, spec: Spec) -> Self {
        Student { name, age, spec }
    }
}

impl ToJson for Student {
    fn to_json(&self) -> String {
        format! (
        r#"{{
            "name": "{}",
            "age": {},
            "spec": {}
        }}"#,
        self.name,
        self.age,
        self.spec.to_json()
        )
    }
}

#[derive(Debug, Clone)]
struct Teacher {
    name: String,
    age: u32,
    spec: Vec<Spec>,
    title: Title,
}

impl Teacher {
    fn new(name: String, age: u32, spec: Vec<Spec>, title: Title) -> Self {
        Teacher { name, age, spec, title }
    }
}

impl ToJson for Teacher {
    fn to_json(&self) -> String {
        let mut iter = self.spec.iter();

        let mut result = match iter.next() {
            Some(first) => first.to_json(),
            None => String::new(),
        };

        for e in iter {
            result.push_str(", ");
            result.push_str(&e.to_json());
        }

        format!(
            r#"{{"name": "{}", "age": {}, "spec": [{}], "title": {}}}"#,
            self.name, self.age, result, self.title.to_json()
        )
    }
}

#[derive(Debug)]
struct University {
    name: String,
    students: Vec<Box<dyn ToJson>>,
    teachers: Vec<Box<dyn ToJson>>,
}

impl University {
    fn new<S: ToJson + 'static, T: ToJson + 'static>(
        name: String,
        students: Vec<S>,
        teachers: Vec<T>,
    ) -> Self {
        let mut s_vec: Vec<Box<dyn ToJson>> = Vec::new();
        for s in students {
            s_vec.push(Box::new(s));
        }

        let mut t_vec: Vec<Box<dyn ToJson>> = Vec::new();
        for t in teachers {
            t_vec.push(Box::new(t));
        }

        University {
            name,
            students: s_vec,
            teachers: t_vec,
        }
    }
}

impl ToJson for University {
    fn to_json(&self) -> String {
        let mut iter_s = self.students.iter();
        let mut iter_t = self.teachers.iter();

        let mut res_s = match iter_s.next() {
            Some(first) => first.to_json(),
            None => String::new(),
        };

        for e in iter_s {
            res_s.push_str(", ");
            res_s.push_str(&e.to_json());
        }

        let mut res_t = match iter_t.next() {
            Some(first) => first.to_json(),
            None => String::new(),
        };

        for e in iter_t {
            res_t.push_str(", ");
            res_t.push_str(&e.to_json());
        }

        format!(
            r#"{{"name": "{}", "students": [{}], "teachers": [{}]}}"#,
            self.name, res_s, res_t
        )
    }
}

fn main() {
   let s1 = Student::new("Ivan".to_string(), 20, Spec::SI);
   let s2 = Student::new("Peter".to_string(), 25, Spec::SI);
   let t1 = Teacher::new(
    "Dr. Petrov".to_string(),
    45,
    vec![Spec::SI, Spec::IS],
    Title::Professor,
    );

    let uni = University::new("SU".to_string(), vec![s1, s2], vec![t1]);
    println!("{}", uni.to_json());
}


