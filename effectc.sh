for c in 2 3 4 5
do
    ./DATALOADER -map OL -print 0 -k 30 -nq 50 -nc $c -seed 100 -algo "prunedij"
done

for c in 2 3 4 5
do
    ./DATALOADER -map OL -print 0 -k 30 -nq 50 -nc $c -seed 100 -algo "prunefnn"
done

for c in 2 3 4 5
do
    ./DATALOADER -map TG -print 0 -k 30 -nq 50 -nc $c -seed 100 -algo "prunedij"
done

for c in 2 3 4 5
do
    ./DATALOADER -map TG -print 0 -k 30 -nq 50 -nc $c -seed 100 -algo "prunefnn"
done

for c in 2 3 4 5
do
    ./DATALOADER -map CAL -print 0 -k 30 -nq 50 -nc $c -seed 100 -algo "prunedij"
done

for c in 2 3 4 5
do
    ./DATALOADER -map CAL -print 0 -k 30 -nq 50 -nc $c -seed 100 -algo "prunefnn"
done