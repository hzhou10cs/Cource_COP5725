for c in 2 3 4 5
do
    ./DATALOADER -map cal -print 0 -k 30 -nq 50 -nc $c -seed 100 -algo "prunedij"
done

for c in 2 3 4 5
do
    ./DATALOADER -map cal -print 0 -k 30 -nq 50 -nc $c -seed 100 -algo "prunefnn"
done
