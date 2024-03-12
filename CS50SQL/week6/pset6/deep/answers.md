# From the Deep

In this problem, you'll write freeform responses to the questions provided in the specification.

## Random Partitioning

Reasons to use: guaranteed that data is evenly distributed.

Reasons not to use: longer process to query all the data, independent of the query as it is all randomized.

## Partitioning by Hour

Reasons to use: faster to find the data and query.

Reasons not to use: data will not be distributed evenly, one boat would be with lots of data and others might not be being used at all.

## Partitioning by Hash Value

Reasons to use: even load of data on all boats and reusing the hash function could help find specific observations.

Reasons not to use: still longer to process all data for a given set of time.
