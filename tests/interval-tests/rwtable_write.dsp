// The write index is out of the table ([-50:50]), the read index within it (0) : the
// write keeps its guard.
process(x, y) = rwtable(100, 0.0, int(x * 50.0), y, 0);
