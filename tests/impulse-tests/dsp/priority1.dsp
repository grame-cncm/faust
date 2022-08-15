smooth_imp = case { 
  // y[n] = (1 - s) * x[n] + s * y[n - 1]
  (0,s) => \(x).(fb ~ _ with { fb(y) = (1.0 - s) * x + s * y; });
  
  // y[n] = s * (y[n - 1] - x[n]) + x[n]
  (1,s) => \(x).(fb ~ _ with { fb(y) = s * (y - x) + x; });
  
  // y[n] = y[n - 1] + (1 - s) * (x[n] - y[n - 1])
  (2,s) => \(x).(fb ~ _ with { fb(y) = y + (1.0 - s) * (x - y); });
};

smooth = smooth_imp(0);
smoo = smooth(0.9);

op1 = _*10.5 : smoo;
op2 = int(_*10.5) : smoo;

op3 = int(_*3.5);
op4 = int(_)+3;

out1 = op1 * op1 * op1;
out2 = (op1 * op1) * op1;
out3 = op1 * (op1 * op1);

out4 = op1 * op1 + op1;
out5 = (op1 * op1) + op1;
out6 = op1 * (op1 + op1);

out7 = (op3 * op3 % op4) : smoo;
out8 = ((op3 * op3) % op4) : smoo;
out9 = (op3 * (op3 % op4)) : smoo;

out10 = (op3 << op3 >> op4) : smoo;
out11 = ((op3 << op3) >> op4) : smoo;
out12 = (op3 << (op3 >> op4)) : smoo;

out13 = (op3 << op3 <= op4) : smoo;
out14 = ((op3 << op3) <= op4) : smoo;
out15 = (op3 << (op3 <= op4)) : smoo;

out16 = (op3 < op3 <= op4) : smoo;
out17 = ((op3 < op3) <= op4) : smoo;
out18 = (op3 < (op3 <= op4)) : smoo;

out19 = (op3 == op3 != op4) : smoo;
out20 = ((op3 == op3) != op4) : smoo;
out21 = (op3 == (op3 != op4)) : smoo;

out22 = (op3 & op3 | op4) : smoo;
out23 = (op3 & op3 xor op4) : smoo;
out24 = ((op3 & op3) | op4) : smoo;
out25 = ((op3 & op3) xor op4) : smoo;
out26 = (op3 & (op3 | op4)) : smoo;
out27 = (op3 & (op3 xor op4)) : smoo;

out28 = op3 + op4 - op3 | op4 : smoo;
out29 = op3 * op4 / op3 % op4 & op3 xor op4 << op3 >> op4 : smoo;

out30 = (op3 <= op4 >= op3 + op4 - op3 | op4) : smoo;
out31 = (op4 + op3 - op4 | op3 * op4 / op3 % op4 & op3 xor op4 << op3 >> op4) : smoo;

process = out1, out2, out3, out4, out5, out6, out7, out8, out9, out10,
    out11, out12, out13, out14, out15, out16, out17, out18, out19, out20,
    out21, out22, out23, out24, out25, out26, out27, out28, out29,
    out30, out31; 
