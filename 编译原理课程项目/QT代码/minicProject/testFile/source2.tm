* C- Compilation to TM Code
* File: E:/QTproject/minicProject/testFile/source2.tm
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
 27:    LDA  2,-4(5) 	get local address
* <- Id
 28:    LDA  4,-1(4) 	push prepare
 29:     ST  2,0(4) 	protect bx
* -> Id
 30:    LDA  2,2(5) 	get param variable address
 31:     LD  1,0(2) 	get variable value
* <- Id
 32:    LDA  4,1(4) 	pop prepare
 33:     LD  2,-1(4) 	recover bx
 34:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> Id
 35:    LDA  2,2(5) 	get param variable address
* <- Id
 36:    LDA  4,-1(4) 	push prepare
 37:     ST  2,0(4) 	protect bx
 38:    LDA  4,1(4) 	pop prepare
 39:     LD  2,-1(4) 	recover bx
 40:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> Id
 41:    LDA  2,-3(5) 	get local address
* <- Id
 42:    LDA  4,-1(4) 	push prepare
 43:     ST  2,0(4) 	protect bx
* -> Op
* -> Id
 44:    LDA  2,2(5) 	get param variable address
 45:     LD  1,0(2) 	get variable value
* <- Id
 46:    LDA  4,-1(4) 	push prepare
 47:     ST  1,0(4) 	op: protect left
* -> Const
 48:    LDC  1,1(0) 	load const
* <- Const
 49:    LDA  4,1(4) 	pop prepare
 50:     LD  2,-1(4) 	op: recover left
 51:    ADD  1,2,1 	op +
* <- Op
 52:    LDA  4,1(4) 	pop prepare
 53:     LD  2,-1(4) 	recover bx
 54:     ST  1,0(2) 	assign: store
* <- assign
* -> while
* jump here after body
* -> Op
* -> Id
 55:    LDA  2,-3(5) 	get local address
 56:     LD  1,0(2) 	get variable value
* <- Id
 57:    LDA  4,-1(4) 	push prepare
 58:     ST  1,0(4) 	op: protect left
* -> Id
 59:    LDA  2,3(5) 	get param variable address
 60:     LD  1,0(2) 	get variable value
* <- Id
 61:    LDA  4,1(4) 	pop prepare
 62:     LD  2,-1(4) 	op: recover left
 63:    SUB  1,2,1 	op <
 64:    JLT  1,2(7) 	br if true
 65:    LDC  1,0(0) 	false case
 66:    LDA  7,1(7) 	unconditional jmp
 67:    LDC  1,1(0) 	true case
* <- Op
* jump to end if test fails
* -> compound
* -> if
* -> Op
 69:    LDA  4,-1(4) 	push prepare
 70:     ST  1,0(4) 	op: protect left
* -> Id
 71:    LDA  2,2(5) 	get param variable address
 72:     LD  1,0(2) 	get variable value
* <- Id
 73:    LDA  4,1(4) 	pop prepare
 74:     LD  2,-1(4) 	op: recover left
 75:    SUB  1,2,1 	op <
 76:    JLT  1,2(7) 	br if true
 77:    LDC  1,0(0) 	false case
 78:    LDA  7,1(7) 	unconditional jmp
 79:    LDC  1,1(0) 	true case
* <- Op
* if: jump to else belongs here
* -> compound
* -> assign
* -> Id
 81:    LDA  2,2(5) 	get param variable address
* <- Id
 82:    LDA  4,-1(4) 	push prepare
 83:     ST  2,0(4) 	protect bx
* -> array element
 84:     LD  2,2(5) 	get param array address
 85:    LDA  4,-1(4) 	push prepare
 86:     ST  2,0(4) 	protect array address
* -> Id
 87:    LDA  2,-3(5) 	get local address
 88:     LD  1,0(2) 	get variable value
* <- Id
 89:    LDA  4,1(4) 	pop prepare
 90:     LD  2,-1(4) 	recover array address
 91:    SUB  2,2,1 	get address of array element
 92:     LD  1,0(2) 	get value of array element
* <- array element
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
 99:    LDA  2,-2(5) 	get local array address
100:    LDA  2,0(2) 	get array variable value
* <- Id
101:    LDA  4,1(4) 	pop prepare
102:     LD  2,-1(4) 	recover bx
103:     ST  1,0(2) 	assign: store
* <- assign
* <- compound
* if: jump to end belongs here
 80:    JEQ  1,24(7) 	if: jmp to else
104:    LDA  7,0(7) 	jmp to end
* <- if
* -> assign
* -> Id
105:    LDA  2,-2(5) 	get local array address
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
119:    LDA  7,55(0) 	jump to test
 68:    JEQ  1,120(0) 	jump to end
* <- while
* -> return
* -> Id
120:    LDA  2,-3(5) 	get local array address
121:    LDA  2,0(2) 	get array variable value
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
133:     LD  2,6(5) 	get param array address
134:    LDA  2,0(2) 	get array variable value
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
158:    LDA  2,-2(5) 	get local array address
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
169:     LD  2,2(5) 	get param array address
170:    LDA  2,0(2) 	get array variable value
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
* -> array element
184:     LD  2,2(5) 	get param array address
185:    LDA  4,-1(4) 	push prepare
186:     ST  2,0(4) 	protect array address
* -> Id
187:    LDA  2,-2(5) 	get local array address
188:    LDA  2,0(2) 	get array variable value
* <- Id
189:    LDA  4,1(4) 	pop prepare
190:     LD  2,-1(4) 	recover array address
191:    SUB  2,2,1 	get address of array element
192:     LD  1,0(2) 	get value of array element
* <- array element
193:    LDA  4,1(4) 	pop prepare
194:     LD  2,-1(4) 	recover bx
195:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> array element
196:     LD  2,2(5) 	get param array address
197:    LDA  4,-1(4) 	push prepare
198:     ST  2,0(4) 	protect array address
* -> Id
199:    LDA  2,-3(5) 	get local address
200:     LD  1,0(2) 	get variable value
* <- Id
201:    LDA  4,1(4) 	pop prepare
202:     LD  2,-1(4) 	recover array address
203:    SUB  2,2,1 	get address of array element
* <- array element
204:    LDA  4,-1(4) 	push prepare
205:     ST  2,0(4) 	protect bx
* -> array element
206:     LD  2,2(5) 	get param array address
207:    LDA  4,-1(4) 	push prepare
208:     ST  2,0(4) 	protect array address
* -> Id
209:    LDA  2,-2(5) 	get local address
210:     LD  1,0(2) 	get variable value
* <- Id
211:    LDA  4,1(4) 	pop prepare
212:     LD  2,-1(4) 	recover array address
213:    SUB  2,2,1 	get address of array element
214:     LD  1,0(2) 	get value of array element
* <- array element
215:    LDA  4,1(4) 	pop prepare
216:     LD  2,-1(4) 	recover bx
217:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> array element
218:     LD  2,2(5) 	get param array address
219:    LDA  4,-1(4) 	push prepare
220:     ST  2,0(4) 	protect array address
* -> Id
221:    LDA  2,-2(5) 	get local address
222:     LD  1,0(2) 	get variable value
* <- Id
223:    LDA  4,1(4) 	pop prepare
224:     LD  2,-1(4) 	recover array address
225:    SUB  2,2,1 	get address of array element
* <- array element
226:    LDA  4,-1(4) 	push prepare
227:     ST  2,0(4) 	protect bx
* -> Id
228:    LDA  2,-4(5) 	get local address
229:     LD  1,0(2) 	get variable value
* <- Id
230:    LDA  4,1(4) 	pop prepare
231:     LD  2,-1(4) 	recover bx
232:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> Id
233:    LDA  2,-2(5) 	get local address
* <- Id
234:    LDA  4,-1(4) 	push prepare
235:     ST  2,0(4) 	protect bx
* -> Op
* -> Id
236:    LDA  2,-2(5) 	get local address
237:     LD  1,0(2) 	get variable value
* <- Id
238:    LDA  4,-1(4) 	push prepare
239:     ST  1,0(4) 	op: protect left
* -> Const
240:    LDC  1,1(0) 	load const
* <- Const
241:    LDA  4,1(4) 	pop prepare
242:     LD  2,-1(4) 	op: recover left
243:    ADD  1,2,1 	op +
* <- Op
244:    LDA  4,1(4) 	pop prepare
245:     LD  2,-1(4) 	recover bx
246:     ST  1,0(2) 	assign: store
* <- assign
* <- compound
247:    LDA  7,138(0) 	jump to test
157:    JEQ  1,248(0) 	jump to end
* <- while
* <- compound
248:    LDA  4,0(5) 	let sp == bp
249:    LDA  4,2(4) 	pop prepare
250:     LD  5,-2(4) 	pop old bp
251:     LD  7,-1(4) 	pop return addr
* <- function
* -> function:
252:    LDA  4,-1(4) 	push prepare
253:     ST  5,0(4) 	push old bp
254:    LDA  5,0(4) 	let bp == sp
255:    LDA  4,-1(4) 	allocate for local variables
* -> compound
* -> assign
* -> Id
256:    LDA  2,-2(5) 	get local address
* <- Id
257:    LDA  4,-1(4) 	push prepare
258:     ST  2,0(4) 	protect bx
* -> Const
259:    LDC  1,0(0) 	load const
* <- Const
260:    LDA  4,1(4) 	pop prepare
261:     LD  2,-1(4) 	recover bx
262:     ST  1,0(2) 	assign: store
* <- assign
* -> while
* jump here after body
* -> Op
* -> Id
263:    LDA  2,-2(5) 	get local address
264:     LD  1,0(2) 	get variable value
* <- Id
265:    LDA  4,-1(4) 	push prepare
266:     ST  1,0(4) 	op: protect left
* -> Const
267:    LDC  1,10(0) 	load const
* <- Const
268:    LDA  4,1(4) 	pop prepare
269:     LD  2,-1(4) 	op: recover left
270:    SUB  1,2,1 	op <
271:    JLT  1,2(7) 	br if true
272:    LDC  1,0(0) 	false case
273:    LDA  7,1(7) 	unconditional jmp
274:    LDC  1,1(0) 	true case
* <- Op
* jump to end if test fails
* -> compound
* -> assign
276:    LDA  4,-1(4) 	push prepare
277:     ST  2,0(4) 	protect bx
* -> call
278:    LDA  1,3(7) 	store returned PC
279:    LDA  4,-1(4) 	push prepare
280:     ST  1,0(4) 	push returned PC
281:    LDC  7,9(0) 	jump to function
282:    LDA  4,0(4) 	release parameters
* <- call
283:    LDA  4,1(4) 	pop prepare
284:     LD  2,-1(4) 	recover bx
285:     ST  1,0(2) 	assign: store
* <- assign
* -> assign
* -> Id
286:    LDA  2,-1(5) 	get local array address
* <- Id
287:    LDA  4,-1(4) 	push prepare
288:     ST  2,0(4) 	protect bx
* -> Op
* -> Id
289:    LDA  2,-2(5) 	get local address
290:     LD  1,0(2) 	get variable value
* <- Id
291:    LDA  4,-1(4) 	push prepare
292:     ST  1,0(4) 	op: protect left
* -> Const
293:    LDC  1,1(0) 	load const
* <- Const
294:    LDA  4,1(4) 	pop prepare
295:     LD  2,-1(4) 	op: recover left
296:    ADD  1,2,1 	op +
* <- Op
297:    LDA  4,1(4) 	pop prepare
298:     LD  2,-1(4) 	recover bx
299:     ST  1,0(2) 	assign: store
* <- assign
* <- compound
300:    LDA  7,263(0) 	jump to test
275:    JEQ  1,301(0) 	jump to end
* <- while
* -> call
* -> Const
301:    LDC  1,10(0) 	load const
* <- Const
302:    LDA  4,-1(4) 	push prepare
303:     ST  1,0(4) 	push parameters
* -> Const
304:    LDC  1,0(0) 	load const
* <- Const
305:    LDA  4,-1(4) 	push prepare
306:     ST  1,0(4) 	push parameters
* -> Id
307:    LDA  2,-3(5) 	get local address
308:     LD  1,0(2) 	get variable value
* <- Id
309:    LDA  4,-1(4) 	push prepare
310:     ST  1,0(4) 	push parameters
311:    LDA  1,3(7) 	store returned PC
312:    LDA  4,-1(4) 	push prepare
313:     ST  1,0(4) 	push returned PC
314:    LDC  7,126(0) 	jump to function
315:    LDA  4,3(4) 	release parameters
* <- call
* -> assign
* -> Id
316:    LDA  2,-2(5) 	get local address
* <- Id
317:    LDA  4,-1(4) 	push prepare
318:     ST  2,0(4) 	protect bx
* -> Const
319:    LDC  1,0(0) 	load const
* <- Const
320:    LDA  4,1(4) 	pop prepare
321:     LD  2,-1(4) 	recover bx
322:     ST  1,0(2) 	assign: store
* <- assign
* -> while
* jump here after body
* -> Op
* -> Id
323:    LDA  2,-1(5) 	get local array address
324:    LDA  2,0(2) 	get array variable value
* <- Id
325:    LDA  4,-1(4) 	push prepare
326:     ST  1,0(4) 	op: protect left
* -> Const
327:    LDC  1,10(0) 	load const
* <- Const
328:    LDA  4,1(4) 	pop prepare
329:     LD  2,-1(4) 	op: recover left
330:    SUB  1,2,1 	op <
331:    JLT  1,2(7) 	br if true
332:    LDC  1,0(0) 	false case
333:    LDA  7,1(7) 	unconditional jmp
334:    LDC  1,1(0) 	true case
* <- Op
* jump to end if test fails
* -> compound
* -> call
* -> array element
336:     LD  2,2(5) 	get param array address
337:    LDA  4,-1(4) 	push prepare
338:     ST  2,0(4) 	protect array address
* -> Id
339:    LDA  2,-2(5) 	get local address
340:     LD  1,0(2) 	get variable value
* <- Id
341:    LDA  4,1(4) 	pop prepare
342:     LD  2,-1(4) 	recover array address
343:    SUB  2,2,1 	get address of array element
344:     LD  1,0(2) 	get value of array element
* <- array element
345:    LDA  4,-1(4) 	push prepare
346:     ST  1,0(4) 	push parameters
347:    LDA  1,3(7) 	store returned PC
348:    LDA  4,-1(4) 	push prepare
349:     ST  1,0(4) 	push returned PC
350:    LDC  7,12(0) 	jump to function
351:    LDA  4,1(4) 	release parameters
* <- call
* -> assign
* -> Id
352:    LDA  2,-2(5) 	get local address
* <- Id
353:    LDA  4,-1(4) 	push prepare
354:     ST  2,0(4) 	protect bx
* -> Op
* -> Id
355:    LDA  2,-2(5) 	get local address
356:     LD  1,0(2) 	get variable value
* <- Id
357:    LDA  4,-1(4) 	push prepare
358:     ST  1,0(4) 	op: protect left
* -> Const
359:    LDC  1,1(0) 	load const
* <- Const
360:    LDA  4,1(4) 	pop prepare
361:     LD  2,-1(4) 	op: recover left
362:    ADD  1,2,1 	op +
* <- Op
363:    LDA  4,1(4) 	pop prepare
364:     LD  2,-1(4) 	recover bx
365:     ST  1,0(2) 	assign: store
* <- assign
* <- compound
366:    LDA  7,323(0) 	jump to test
335:    JEQ  1,367(0) 	jump to end
* <- while
* <- compound
367:    LDA  4,0(5) 	let sp == bp
368:    LDA  4,2(4) 	pop prepare
369:     LD  5,-2(4) 	pop old bp
370:     LD  7,-1(4) 	pop return addr
* <- function
  3:    LDA  1,3(7) 	store returned PC
  4:    LDA  4,-1(4) 	push prepare
  5:     ST  1,0(4) 	push returned PC
  6:    LDC  7,252(0) 	jump to function
  7:    LDA  4,0(4) 	release local var
* End of execution.
  8:   HALT  0,0,0 	

Code generated in file E:/QTproject/minicProject/testFile/source2.tm
