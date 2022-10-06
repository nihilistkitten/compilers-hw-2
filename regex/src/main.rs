use clap::Parser;
use plex::lexer;

#[derive(Parser, Debug)]
#[clap(author, version, about, long_about = None)]
struct Args {
    /// Name of the person to greet
    #[clap(value_parser)]
    file: String,
}

macro_rules! lx {
    ($name:ident: $regex:expr) => {
        lexer! {
            fn $name(tok) -> ();
            $regex => println!("{tok} YES", tok=tok.trim()),
            "[^\n]*\n" => println!("{tok} NO", tok=tok.trim()),
        }
    }
}

lx!(abc: "a*b*c*\n");
lx!(zero_one_one: "1*(0+1)*0*\n");
lx!(even_0_1: "((00)|(11)|(((10)|(01))((00)|(11))*((10)|(01))))*\n");

fn main() -> anyhow::Result<()> {
    let args = Args::parse();

    let orig = std::fs::read_to_string(args.file)?;
    let mut file = orig.as_str();
    while !file.is_empty() {
        file = even_0_1(file).unwrap().1;
    }

    Ok(())
}
