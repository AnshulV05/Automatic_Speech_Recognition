name=$1
fstdraw "$1".fst "$1".dot
dot -Tpdf "$1".dot > "$1".pdf