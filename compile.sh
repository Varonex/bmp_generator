if [ $# -lt 1 ]; then
    echo "Erreur: aucun main précisé." >&2 && exit 1
fi

if [ ! -f "run/$1.c" ]; then
    echo "Erreur: fichier \"run/$1.c\" inexistant." >&2 && exit
fi

fn="$1"
shift

gcc -o bin.exe src/*.c -Iinclude "run/$fn.c" -lm && ./bin.exe