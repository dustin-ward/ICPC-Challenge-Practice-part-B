# ICPC-Challenge-Practice-part-B
Multiple attempts at part B of the ICPC Challenge Practice contest

This is a repository containing my solutions to the ICPC Challenge Practice part B

The problem was to find the largest possible independent set in a given graph. (Independent meaning the set cannot contain two vertices that are directly connected by an edge in the graph). The score you receive is based on the size of the set you find.

## Compiling

I have been compiling the programs with the following command:

`g++ -std=c++11 -o Bv1 Bv1.cpp -Wall`

## Solution 1

My approach in this version was to simply include node 1 in my set, then mark all its neighbors as unavailable. I would then scan for the next unmarked node, and repeat the process. The end result would be a maximal independent set that includes node 1. The scores I acheived with this program are as follows:

>B1: 2480
>B2: 31736
>B3: 30301
>B4: 50316

## Solution 2

The problem with my initial attempt was that node 1 HAD to be included in the set. With the large input size, the chance that node 1 was part of the large solution wasn't 100%. The work around seemed to be that If I could start my search on a bunch of random nodes, I could then just take the max score I recieve. The array 'r' serves as an ordering of nodes to visit. I then just shuffle the array and the result is a new ordering to try.

I've also added an iteration feature to this one, so you can control the number of times a result is generated. I usually run the smaller sets around 1000 times. This really didnt seem to improve my initial scores. Finding the correct starting node is really hard, and even then, there is probably a better way to generate the rest of the set. Here are the scores I got:

?B1: 2488
>B2: 31835
>B3: 30447
>B4: 50481

## Solution 3

After randomizing the starting node in my last attemp didn't yeild much of an improvement, I needed to generate my sets in a different way. The easiest way would be to always choose the lowest degree node instead of a random one. This way I don't mark off as many nodes initially. So on input, I keep track of the cannections to any given node, then I cn just sort my ordering based on the degree of each node and always choose the lowest one available.

>B1: 2740
>B2: 35502
>B3: 34934
>B4: 58233
