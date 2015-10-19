0:mar := pc; rd;                                          { main loop }
1:pc := 1 + pc; rd;                                       { increment pc }
2:ir := mbr; if n then goto 28;                           { save, decode mbr }
3:tir := lshift(ir + ir); if n then goto 19;
4:tir := lshift(tir); if n then goto 11;                  { 000x or 001x? }
5:alu := tir; if n then goto 9;                           { 0000 or 0001? }
6:mar := ir; rd;                                          { 0000 = LODD }
7:rd;
8:ac := mbr; goto 0;
9:mar := ir; mbr := ac; wr;                               { 0001 = STOD }
10:wr; goto 0;
11:alu := tir; if n then goto 15;                         { 0010 or 0011? }
12:mar := ir; rd;                                         { 0010 = ADDD }
13:rd;
14:ac := ac + mbr; goto 0;
15:mar := ir; rd;                                         { 0011 = SUBD }
16:ac := 1 + ac; rd;                                      { Note: x - y = x + 1 + not y }
17:a := inv(mbr);
18:ac := a + ac; goto 0;
19:tir := lshift(tir); if n then goto 25;                 { 010x or 011x? }
20:alu := tir; if n then goto 23;                         { 0100 or 0101? }
21:alu := ac; if n then goto 0;                           { 0100 = JPOS }
22:pc := band(ir, amask); goto 0;                         { perform the jump }
23:alu := ac; if z then goto 22;                          { 0101 = JZER }
24:goto 0;                                                { jump failed }
25:alu := tir; if n then goto 27;                         { 0110 or 0111? }
26:pc := band(ir, amask); goto 0;                         { 0110 = JUMP }
27:ac := band(ir, amask); goto 0;                         { 0111 = LOCO }
28:tir := lshift(ir + ir); if n then goto 40;             { 10xx or 11xx? }
29:tir := lshift(tir); if n then goto 35;                 { 100x or 101x? }
30:alu := tir; if n then goto 33;                         { 1000 or 1001? }
31:a := sp + ir;                                          { 1000 = LODL }
32:mar := a; rd; goto 7;
33:a := sp + ir;                                          { 1001 = STOL }
34:mar := a; mbr := ac; wr; goto 10;
35:alu := tir; if n then goto 38;                         { 1010 or 1011? }
36:a := sp + ir;                                          { 1010 = ADDL }
37:mar := a; rd; goto 13;
38:a := sp + ir;                                          { 1011 = SUBL }
39:mar := a; rd; goto 16;
40:tir := lshift(tir); if n then goto 46;                 { 110x or 111x? }
41:alu := tir; if n then goto 44;                         { 1100 or 1101? }
42:alu := ac; if n then goto 22;                          { 1100 = JNEG }
43:goto 0;
44:alu := ac; if z then goto 0;                           { 1101 = JNZE }
45:pc := band(ir, amask); goto 0;
46:tir := lshift(tir); if n then goto 50;
47:sp := sp + (-1);                                       { 1110 = CALL }
48:mar := sp; mbr := pc; wr;
49:pc := band(ir, amask); wr; goto 0;
50:tir := lshift(tir); if n then goto 65;                 { 1111, examine addr }
51:tir := lshift(tir); if n then goto 59;
52:alu := tir; if n then goto 56;
53:mar := ac; rd;                                         { 1111000 = PSHI }
54:sp := sp + (-1); rd;
55:mar := sp; wr; goto 10;
56:mar := sp; sp := sp + 1; rd;                           { 1111001 = POPI }
57:rd;
58:mar := ac; wr; goto 10;
59:alu := tir; if n then goto 62;
60:sp := sp + (-1);                                       { 1111010 = PUSH }
61:mar := sp; mbr := ac; wr; goto 10;
62:mar := sp; sp := sp + 1; rd;                           { 1111011 = POP }
63:rd;
64:ac := mbr; goto 0;
65:tir := lshift(tir); if n then goto 73;
66:alu := tir; if n then goto 70;
67:mar := sp; sp := sp + 1; rd;                           { 1111100 = RETN }
68:rd;
69:pc := mbr; goto 0;
70:a := ac;                                               { 1111101 = SWAP }
71:ac := sp;
72:sp := a; goto 0;
73:alu := tir; if n then goto 76;
74:a := band(ir, smask);                                  { 1111110 = INSP }
75:sp := sp + a; goto 0;
76:tir := tir + tir; if n then goto 80;
77:a := band(ir, smask);                                  { 11111110 = DESP }
78:a := inv(a);
79:a := a + 1; goto 75;
80:tir := tir + tir; if n then goto 200;                  { 1111 1111 1x = HALT @ line 200 }
81:a := lshift(1);                                        { 1111 1111 01 = RSHIFT }
82:a := lshift(a + 1);
83:a := lshift(a + 1);
84:a := a + 1;
85:b := band(ir, a);
86:b := b + (-1); if n then goto 88;
87:ac := rshift(ac); goto 86;
88:goto 0;
89: goto 0;
90: goto 0;
91: goto 0;
92: goto 0;
93: goto 0;
94: goto 0;
95: goto 0;
96: goto 0;
97: goto 0;
98: goto 0;
99: goto 0;
100: goto 0;
101: goto 0;
102: goto 0;
103: goto 0;
104: goto 0;
105: goto 0;
106: goto 0;
107: goto 0;
108: goto 0;
109: goto 0;
110: goto 0;
111: goto 0;
112: goto 0;
113: goto 0;
114: goto 0;
115: goto 0;
116: goto 0;
117: goto 0;
118: goto 0;
119: goto 0;
120: goto 0;
121: goto 0;
122: goto 0;
123: goto 0;
124: goto 0;
125: goto 0;
126: goto 0;
127: goto 0;
128: goto 0;
129: goto 0;
130: goto 0;
131: goto 0;
132: goto 0;
133: goto 0;
134: goto 0;
135: goto 0;
136: goto 0;
137: goto 0;
138: goto 0;
139: goto 0;
140: goto 0;
141: goto 0;
142: goto 0;
143: goto 0;
144: goto 0;
145: goto 0;
146: goto 0;
147: goto 0;
148: goto 0;
149: goto 0;
150: goto 0;
151: goto 0;
152: goto 0;
153: goto 0;
154: goto 0;
155: goto 0;
156: goto 0;
157: goto 0;
158: goto 0;
159: goto 0;
160: goto 0;
161: goto 0;
162: goto 0;
163: goto 0;
164: goto 0;
165: goto 0;
166: goto 0;
167: goto 0;
168: goto 0;
169: goto 0;
170: goto 0;
171: goto 0;
172: goto 0;
173: goto 0;
174: goto 0;
175: goto 0;
176: goto 0;
177: goto 0;
178: goto 0;
179: goto 0;
180: goto 0;
181: goto 0;
182: goto 0;
183: goto 0;
184: goto 0;
185: goto 0;
186: goto 0;
187: goto 0;
188: goto 0;
189: goto 0;
190: goto 0;
191: goto 0;
192: goto 0;
193: goto 0;
194: goto 0;
195: goto 0;
196: goto 0;
197: goto 0;
198: goto 0;
199: goto 0;
200: rd; wr;                    { 1111 1111 1x = HALT }
