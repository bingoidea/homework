* C- Compilation to TM Code
* File: test2.tm
* Standard prelude:
  0:     LD  6,0(0) 	load maxaddress from location 0
  1:    LDA  4,-10(6) 	copy gp to sp &allocating global variables(if any)
  2:     ST  0,0(0) 	clear location 0
* End of standard prelude.
* Jump to main()
* Begin input()
  9:     IN  1,0,0 	read input into ax
 10:    LDA  4,1(4) 	pop prepare
 11:     LD  7,-1(4) 	pop return addr
* End input()
* Begin output()
 12:     LD  1,1(4) 	load param into ax
 13:    OUT  1,0,0 	output using ax
 14:    LDA  4,1(4) 	pop prepare
 15:     LD  7,-1(4) 	pop return addr
* End output()
* -> array element
 16:     LD  2,2(5) 	get param array address
 17:    LDA  4,-1(4) 	push prepare
 18:     ST  2,0(4) 	protect array address
 19:    LDA  4,1(4) 	pop prepare
 20:     LD  2,-1(4) 	recover array address
 21:    SUB  2,2,1 	get address of array element
 22:     LD  1,0(2) 	get value of array element
* <- array element
* -> function:
 23:    LDA  4,-1(4) 	push prepare
 24:     ST  5,0(4) 	push old bp
 25:    LDA  5,0(4) 	let bp == sp
 26:    LDA  4,-3(4) 	allocate for local variables
* -> compound
* -> assign
* -> Id
 27:    LDA  2,-3(5) 	get local array address
* <- Id
 28:    LDA  4,-1(4) 	push prepare
 29:     ST  2,0(4) 	protect bx
* -> Id
 30:     LD  2,2(5) 	get param array address
 31:    LDA  2,0(2) 	get array variable value
* <- Id
 32:    LDA  4,1(4) 	pop prepare
 33:     LD  2,-1(4) 	recover bx
 34:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> Id
 35:     LD  2,2(5) 	get param array address
* <- Id
 36:    LDA  4,-1(4) 	push prepare
 37:     ST  2,0(4) 	protect bx
* -> array element
 38:     LD  2,2(5) 	get param array address
 39:    LDA  4,-1(4) 	push prepare
 40:     ST  2,0(4) 	protect array address
* -> Id
 41:     LD  2,2(5) 	get param array address
 42:    LDA  2,0(2) 	get array variable value
* <- Id
 43:    LDA  4,1(4) 	pop prepare
 44:     LD  2,-1(4) 	recover array address
 45:    SUB  2,2,1 	get address of array element
 46:     LD  1,0(2) 	get value of array element
* <- array element
 47:    LDA  4,1(4) 	pop prepare
 48:     LD  2,-1(4) 	recover bx
 49:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> Id
 50:    LDA  2,-3(5) 	get local address
* <- Id
 51:    LDA  4,-1(4) 	push prepare
 52:     ST  2,0(4) 	protect bx
* -> Op
* -> Id
 53:    LDA  2,2(5) 	get param variable address
 54:     LD  1,0(2) 	get variable value
* <- Id
 55:    LDA  4,-1(4) 	push prepare
 56:     ST  1,0(4) 	op: protect left
* -> Const
 57:    LDC  1,1(0) 	load const
* <- Const
 58:    LDA  4,1(4) 	pop prepare
 59:     LD  2,-1(4) 	op: recover left
 60:    ADD  1,2,1 	op +
* <- Op
 61:    LDA  4,1(4) 	pop prepare
 62:     LD  2,-1(4) 	recover bx
 63:     ST  1,0(2) 	assign: store
* <- assign
* -> while
* jump here after body
* -> Op
* -> Id
 64:    LDA  2,-3(5) 	get local address
 65:     LD  1,0(2) 	get variable value
* <- Id
 66:    LDA  4,-1(4) 	push prepare
 67:     ST  1,0(4) 	op: protect left
* -> Id
 68:    LDA  2,3(5) 	get param variable address
 69:     LD  1,0(2) 	get variable value
* <- Id
 70:    LDA  4,1(4) 	pop prepare
 71:     LD  2,-1(4) 	op: recover left
 72:    SUB  1,2,1 	op <
 73:    JLT  1,2(7) 	br if true
 74:    LDC  1,0(0) 	false case
 75:    LDA  7,1(7) 	unconditional jmp
 76:    LDC  1,1(0) 	true case
* <- Op
* jump to end if test fails
* -> compound
* -> if
* -> Op
 78:    LDA  4,-1(4) 	push prepare
 79:     ST  1,0(4) 	op: protect left
* -> Id
 80:    LDA  2,2(5) 	get param variable address
 81:     LD  1,0(2) 	get variable value
* <- Id
 82:    LDA  4,1(4) 	pop prepare
 83:     LD  2,-1(4) 	op: recover left
 84:    SUB  1,2,1 	op <
 85:    JLT  1,2(7) 	br if true
 86:    LDC  1,0(0) 	false case
 87:    LDA  7,1(7) 	unconditional jmp
 88:    LDC  1,1(0) 	true case
* <- Op
* if: jump to else belongs here
* -> compound
* -> assign
* -> Id
 90:    LDA  2,2(5) 	get param variable address
* <- Id
 91:    LDA  4,-1(4) 	push prepare
 92:     ST  2,0(4) 	protect bx
 93:    LDA  4,1(4) 	pop prepare
 94:     LD  2,-1(4) 	recover bx
 95:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> Id
 96:    LDA  2,-4(5) 	get local address
* <- Id
 97:    LDA  4,-1(4) 	push prepare
 98:     ST  2,0(4) 	protect bx
* -> Id
 99:    LDA  2,-3(5) 	get local address
100:     LD  1,0(2) 	get variable value
* <- Id
101:    LDA  4,1(4) 	pop prepare
102:     LD  2,-1(4) 	recover bx
103:     ST  1,0(2) 	assign: store
* <- assign
* <- compound
* if: jump to end belongs here
 89:    JEQ  1,15(7) 	if: jmp to else
104:    LDA  7,0(7) 	jmp to end
* <- if
* -> assign
* -> Id
105:    LDA  2,-3(5) 	get local address
* <- Id
106:    LDA  4,-1(4) 	push prepare
107:     ST  2,0(4) 	protect bx
* -> Op
* -> Id
108:    LDA  2,-3(5) 	get local address
109:     LD  1,0(2) 	get variable value
* <- Id
110:    LDA  4,-1(4) 	push prepare
111:     ST  1,0(4) 	op: protect left
* -> Const
112:    LDC  1,1(0) 	load const
* <- Const
113:    LDA  4,1(4) 	pop prepare
114:     LD  2,-1(4) 	op: recover left
115:    ADD  1,2,1 	op +
* <- Op
116:    LDA  4,1(4) 	pop prepare
117:     LD  2,-1(4) 	recover bx
118:     ST  1,0(2) 	assign: store
* <- assign
* <- compound
119:    LDA  7,64(0) 	jump to test
 77:    JEQ  1,120(0) 	jump to end
* <- while
* -> return
* -> Id
120:    LDA  2,-4(5) 	get local address
121:     LD  1,0(2) 	get variable value
* <- Id
122:    LDA  4,0(5) 	let sp == bp
123:    LDA  4,2(4) 	pop prepare
124:     LD  5,-2(4) 	pop old bp
125:     LD  7,-1(4) 	pop return addr
* <- return
* <- compound
* <- function
* -> function:
126:    LDA  4,-1(4) 	push prepare
127:     ST  5,0(4) 	push old bp
128:    LDA  5,0(4) 	let bp == sp
129:    LDA  4,-2(4) 	allocate for local variables
* -> compound
* -> assign
* -> Id
130:    LDA  2,-2(5) 	get local address
* <- Id
131:    LDA  4,-1(4) 	push prepare
132:     ST  2,0(4) 	protect bx
* -> Id
133:    LDA  2,6(5) 	get param variable address
134:     LD  1,0(2) 	get variable value
* <- Id
135:    LDA  4,1(4) 	pop prepare
136:     LD  2,-1(4) 	recover bx
137:     ST  1,0(2) 	assign: store
* <- assign
* -> while
* jump here after body
* -> Op
* -> Id
138:    LDA  2,-2(5) 	get local address
139:     LD  1,0(2) 	get variable value
* <- Id
140:    LDA  4,-1(4) 	push prepare
141:     ST  1,0(4) 	op: protect left
* -> Op
* -> Id
142:     LD  2,7(5) 	get param array address
143:    LDA  2,0(2) 	get array variable value
* <- Id
144:    LDA  4,-1(4) 	push prepare
145:     ST  1,0(4) 	op: protect left
* -> Const
146:    LDC  1,1(0) 	load const
* <- Const
147:    LDA  4,1(4) 	pop prepare
148:     LD  2,-1(4) 	op: recover left
149:    SUB  1,2,1 	op -
* <- Op
150:    LDA  4,1(4) 	pop prepare
151:     LD  2,-1(4) 	op: recover left
152:    SUB  1,2,1 	op <
153:    JLT  1,2(7) 	br if true
154:    LDC  1,0(0) 	false case
155:    LDA  7,1(7) 	unconditional jmp
156:    LDC  1,1(0) 	true case
* <- Op
* jump to end if test fails
* -> compound
* -> assign
* -> Id
158:    LDA  2,-3(5) 	get local address
* <- Id
159:    LDA  4,-1(4) 	push prepare
160:     ST  2,0(4) 	protect bx
* -> call
* -> Id
161:    LDA  2,7(5) 	get param variable address
162:     LD  1,0(2) 	get variable value
* <- Id
163:    LDA  4,-1(4) 	push prepare
164:     ST  1,0(4) 	push parameters
* -> Id
165:    LDA  2,-2(5) 	get local address
166:     LD  1,0(2) 	get variable value
* <- Id
167:    LDA  4,-1(4) 	push prepare
168:     ST  1,0(4) 	push parameters
* -> Id
169:    LDA  2,2(5) 	get param variable address
170:     LD  1,0(2) 	get variable value
* <- Id
171:    LDA  4,-1(4) 	push prepare
172:     ST  1,0(4) 	push parameters
173:    LDA  1,3(7) 	store returned PC
174:    LDA  4,-1(4) 	push prepare
175:     ST  1,0(4) 	push returned PC
176:    LDC  7,23(0) 	jump to function
177:    LDA  4,3(4) 	release parameters
* <- call
178:    LDA  4,1(4) 	pop prepare
179:     LD  2,-1(4) 	recover bx
180:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> Id
181:    LDA  2,-4(5) 	get local address
* <- Id
182:    LDA  4,-1(4) 	push prepare
183:     ST  2,0(4) 	protect bx
184:    LDA  4,1(4) 	pop prepare
185:     LD  2,-1(4) 	recover bx
186:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
187:    LDA  4,-1(4) 	push prepare
188:     ST  2,0(4) 	protect bx
189:    LDA  4,1(4) 	pop prepare
190:     LD  2,-1(4) 	recover bx
191:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
192:    LDA  4,-1(4) 	push prepare
193:     ST  2,0(4) 	protect bx
* -> Id
194:    LDA  2,-4(5) 	get local address
195:     LD  1,0(2) 	get variable value
* <- Id
196:    LDA  4,1(4) 	pop prepare
197:     LD  2,-1(4) 	recover bx
198:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> Id
199:    LDA  2,-2(5) 	get local address
* <- Id
200:    LDA  4,-1(4) 	push prepare
201:     ST  2,0(4) 	protect bx
* -> Op
* -> Id
202:    LDA  2,-2(5) 	get local address
203:     LD  1,0(2) 	get variable value
* <- Id
204:    LDA  4,-1(4) 	push prepare
205:     ST  1,0(4) 	op: protect left
* -> Const
206:    LDC  1,1(0) 	load const
* <- Const
207:    LDA  4,1(4) 	pop prepare
208:     LD  2,-1(4) 	op: recover left
209:    ADD  1,2,1 	op +
* <- Op
210:    LDA  4,1(4) 	pop prepare
211:     LD  2,-1(4) 	recover bx
212:     ST  1,0(2) 	assign: store
* <- assign
* <- compound
213:    LDA  7,138(0) 	jump to test
157:    JEQ  1,214(0) 	jump to end
* <- while
* <- compound
214:    LDA  4,0(5) 	let sp == bp
215:    LDA  4,2(4) 	pop prepare
216:     LD  5,-2(4) 	pop old bp
217:     LD  7,-1(4) 	pop return addr
* <- function
* -> function:
218:    LDA  4,-1(4) 	push prepare
219:     ST  5,0(4) 	push old bp
220:    LDA  5,0(4) 	let bp == sp
221:    LDA  4,-1(4) 	allocate for local variables
* -> compound
* -> assign
* -> Id
222:    LDA  2,-1(5) 	get local address
* <- Id
223:    LDA  4,-1(4) 	push prepare
224:     ST  2,0(4) 	protect bx
* -> Const
225:    LDC  1,0(0) 	load const
* <- Const
226:    LDA  4,1(4) 	pop prepare
227:     LD  2,-1(4) 	recover bx
228:     ST  1,0(2) 	assign: store
* <- assign
* -> while
* jump here after body
* -> Op
* -> Id
229:    LDA  2,-1(5) 	get local address
230:     LD  1,0(2) 	get variable value
* <- Id
231:    LDA  4,-1(4) 	push prepare
232:     ST  1,0(4) 	op: protect left
* -> Const
233:    LDC  1,10(0) 	load const
* <- Const
234:    LDA  4,1(4) 	pop prepare
235:     LD  2,-1(4) 	op: recover left
236:    SUB  1,2,1 	op <
237:    JLT  1,2(7) 	br if true
238:    LDC  1,0(0) 	false case
239:    LDA  7,1(7) 	unconditional jmp
240:    LDC  1,1(0) 	true case
* <- Op
* jump to end if test fails
* -> compound
* -> assign
242:    LDA  4,-1(4) 	push prepare
243:     ST  2,0(4) 	protect bx
* -> call
244:    LDA  1,3(7) 	store returned PC
245:    LDA  4,-1(4) 	push prepare
246:     ST  1,0(4) 	push returned PC
247:    LDC  7,9(0) 	jump to function
248:    LDA  4,0(4) 	release parameters
* <- call
249:    LDA  4,1(4) 	pop prepare
250:     LD  2,-1(4) 	recover bx
251:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> Id
252:    LDA  2,-1(5) 	get local address
* <- Id
253:    LDA  4,-1(4) 	push prepare
254:     ST  2,0(4) 	protect bx
* -> Op
* -> Id
255:    LDA  2,-1(5) 	get local address
256:     LD  1,0(2) 	get variable value
* <- Id
257:    LDA  4,-1(4) 	push prepare
258:     ST  1,0(4) 	op: protect left
* -> Const
259:    LDC  1,1(0) 	load const
* <- Const
260:    LDA  4,1(4) 	pop prepare
261:     LD  2,-1(4) 	op: recover left
262:    ADD  1,2,1 	op +
* <- Op
263:    LDA  4,1(4) 	pop prepare
264:     LD  2,-1(4) 	recover bx
265:     ST  1,0(2) 	assign: store
* <- assign
* <- compound
266:    LDA  7,229(0) 	jump to test
241:    JEQ  1,267(0) 	jump to end
* <- while
* -> call
* -> Const
267:    LDC  1,10(0) 	load const
* <- Const
268:    LDA  4,-1(4) 	push prepare
269:     ST  1,0(4) 	push parameters
* -> Const
270:    LDC  1,0(0) 	load const
* <- Const
271:    LDA  4,-1(4) 	push prepare
272:     ST  1,0(4) 	push parameters
* -> Id
273:    LDA  2,-2(5) 	get local address
274:     LD  1,0(2) 	get variable value
* <- Id
275:    LDA  4,-1(4) 	push prepare
276:     ST  1,0(4) 	push parameters
277:    LDA  1,3(7) 	store returned PC
278:    LDA  4,-1(4) 	push prepare
279:     ST  1,0(4) 	push returned PC
280:    LDC  7,126(0) 	jump to function
281:    LDA  4,3(4) 	release parameters
* <- call
* -> assign
* -> Id
282:    LDA  2,-1(5) 	get local address
* <- Id
283:    LDA  4,-1(4) 	push prepare
284:     ST  2,0(4) 	protect bx
* -> Const
285:    LDC  1,0(0) 	load const
* <- Const
286:    LDA  4,1(4) 	pop prepare
287:     LD  2,-1(4) 	recover bx
288:     ST  1,0(2) 	assign: store
* <- assign
* -> while
* jump here after body
* -> Op
* -> Id
289:    LDA  2,-1(5) 	get local address
290:     LD  1,0(2) 	get variable value
* <- Id
291:    LDA  4,-1(4) 	push prepare
292:     ST  1,0(4) 	op: protect left
* -> Const
293:    LDC  1,10(0) 	load const
* <- Const
294:    LDA  4,1(4) 	pop prepare
295:     LD  2,-1(4) 	op: recover left
296:    SUB  1,2,1 	op <
297:    JLT  1,2(7) 	br if true
298:    LDC  1,0(0) 	false case
299:    LDA  7,1(7) 	unconditional jmp
300:    LDC  1,1(0) 	true case
* <- Op
* jump to end if test fails
* -> compound
* -> call
302:    LDA  4,-1(4) 	push prepare
303:     ST  1,0(4) 	push parameters
304:    LDA  1,3(7) 	store returned PC
305:    LDA  4,-1(4) 	push prepare
306:     ST  1,0(4) 	push returned PC
307:    LDC  7,12(0) 	jump to function
308:    LDA  4,1(4) 	release parameters
* <- call
* -> assign
* -> Id
309:    LDA  2,-1(5) 	get local address
* <- Id
310:    LDA  4,-1(4) 	push prepare
311:     ST  2,0(4) 	protect bx
* -> Op
* -> Id
312:    LDA  2,-1(5) 	get local address
313:     LD  1,0(2) 	get variable value
* <- Id
314:    LDA  4,-1(4) 	push prepare
315:     ST  1,0(4) 	op: protect left
* -> Const
316:    LDC  1,1(0) 	load const
* <- Const
317:    LDA  4,1(4) 	pop prepare
318:     LD  2,-1(4) 	op: recover left
319:    ADD  1,2,1 	op +
* <- Op
320:    LDA  4,1(4) 	pop prepare
321:     LD  2,-1(4) 	recover bx
322:     ST  1,0(2) 	assign: store
* <- assign
* <- compound
323:    LDA  7,289(0) 	jump to test
301:    JEQ  1,324(0) 	jump to end
* <- while
* <- compound
324:    LDA  4,0(5) 	let sp == bp
325:    LDA  4,2(4) 	pop prepare
326:     LD  5,-2(4) 	pop old bp
327:     LD  7,-1(4) 	pop return addr
* <- function
  3:    LDA  1,3(7) 	store returned PC
  4:    LDA  4,-1(4) 	push prepare
  5:     ST  1,0(4) 	push returned PC
  6:    LDC  7,218(0) 	jump to function
  7:    LDA  4,0(4) 	release local var
* End of execution.
  8:   HALT  0,0,0 	
