import("stdfaust.lib");
process = os.osc(400)*vslider("vol1", 0.5, 0, 1, 0.01),os.osc(600)*nentry("vol2", 0.5, 0, 1, 0.01);