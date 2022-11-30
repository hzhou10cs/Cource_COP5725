for k in 10 20 30 40 50
do
    ./DATALOADER -map OL -print 0 -k $k -nq 1 -nc 4 -seed 100 -algo "prunedij"
done

for k in 10 20 30 40 50
do
    ./DATALOADER -map OL -print 0 -k $k -nq 1 -nc 4 -seed 100 -algo "prunefnn"
done

for k in 10 20 30 40 50
do
    ./DATALOADER -map TG -print 0 -k $k -nq 1 -nc 4 -seed 100 -algo "prunedij"
done

for k in 10 20 30 40 50
do
    ./DATALOADER -map TG -print 0 -k $k -nq 1 -nc 4 -seed 100 -algo "prunefnn"
done

for k in 10 20 30 40 50
do
    ./DATALOADER -map cal -print 0 -k $k -nq 1 -nc 4 -seed 100 -algo "prunedij"
done

for k in 10 20 30 40 50
do
    ./DATALOADER -map cal -print 0 -k $k -nq 1 -nc 4 -seed 100 -algo "prunefnn"
done
