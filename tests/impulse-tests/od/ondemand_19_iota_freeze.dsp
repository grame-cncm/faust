import("stdfaust.lib");

gate = checkbox("gate") == 0;
delaySamps = 16;

counter = +(1)~_;
delayed = counter : @(delaySamps);
delta = counter - delayed;

process = gate : ondemand(delta);
