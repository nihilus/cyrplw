#ifndef RP_X86_INCLUDED
#define RP_X86_INCLUDED		"Written by Red Plait, February 2000"

#define Ix86_aaa	1
#define Ix86_aad	2
#define Ix86_aam	3
#define Ix86_aas	4
#define Ix86_adc	5
#define Ix86_add	6
#define Ix86_and	7
#define Ix86_arpl	8	/* */
#define Ix86_bound	9	/* */
#define Ix86_bsf	10
#define Ix86_bsr	11
#define Ix86_bt		12
#define Ix86_btc	13
#define Ix86_btr	14
#define Ix86_bts	15
#define Ix86_call	16 /* ordinary call imm value */
#define Ix86_callfi	17 /* ??? */
#define Ix86_callni	18 /* call register */
#define Ix86_cbw	19
#define Ix86_cwde	20	/* */
#define Ix86_cdqe 	21
#define Ix86_clc	22
#define Ix86_cld	23
#define Ix86_cli	24
#define Ix86_clts	25
#define Ix86_cmc	26
#define Ix86_cmp	27
#define Ix86_cmpsb	28
#define Ix86_cwd	29
#define Ix86_cdq	30
#define Ix86_cqo 	31
#define Ix86_daa	32
#define Ix86_das	33
#define Ix86_dec	34
#define Ix86_div	35
#define Ix86_enterw	36	/* */
#define Ix86_enter	37
#define Ix86_enterd	38	/* */
#define Ix86_enterq 	39
#define Ix86_hlt	40
#define Ix86_idiv	41
#define Ix86_imul	42
#define Ix86_in		43
#define Ix86_inc	44
#define Ix86_ins	45
#define Ix86_int	46
#define Ix86_into	47
#define Ix86_int3	48 /* ??? */
#define Ix86_iretw	49	/* */
#define Ix86_iret	50
#define Ix86_iretd	51	/* */
#define Ix86_iretq 	52
#define Ix86_ja		53
#define Ix86_jae	54	/* */
#define Ix86_jb		55
#define Ix86_jbe	56
#define Ix86_jc		57	/* */
#define Ix86_jcxz	58	/* */
#define Ix86_jecxz	59
#define Ix86_jrcxz 	60
#define Ix86_je		61	/* */
#define Ix86_jg		62
#define Ix86_jge	63
#define Ix86_jl		64
#define Ix86_jle	65
#define Ix86_jna	66	/* */
#define Ix86_jnae	67	/* */
#define Ix86_jnb	68
#define Ix86_jnbe	69	/* */
#define Ix86_jnc	70	/* */
#define Ix86_jne	71	/* */
#define Ix86_jng	72	/* */
#define Ix86_jnge	73	/* */
#define Ix86_jnl	74	/* */
#define Ix86_jnle	75	/* */
#define Ix86_jno	76
#define Ix86_jnp	77
#define Ix86_jns	78
#define Ix86_jnz	79
#define Ix86_jo		80
#define Ix86_jp		81
#define Ix86_jpe	82	/* */
#define Ix86_jpo	83	/* */
#define Ix86_js		84
#define Ix86_jz		85
#define Ix86_jmp	86 /* ordinary jmp imm value */
#define Ix86_jmpfi	87 /* ??? */
#define Ix86_jmpni	88 /* jmp register */
#define Ix86_jmpshort	89 /* short jump */
#define Ix86_lahf	90
#define Ix86_lar	91	/* */
#define Ix86_lea	92
#define Ix86_leavew	93	/* */
#define Ix86_leave	94
#define Ix86_leaved	95	/* */
#define Ix86_leaveq 	96
#define Ix86_lgdt	97	/* */
#define Ix86_lidt	98	/* */
#define Ix86_lgs	99	/* */
#define Ix86_lss	100	/* */
#define Ix86_lds	101	/* */
#define Ix86_les	102
#define Ix86_lfs	103	/* */
#define Ix86_lldt	104	/* */
#define Ix86_lmsw	105	/* */
#define Ix86_lock	106
#define Ix86_lods	107
#define Ix86_loopw	108	/* */
#define Ix86_loop	109	/* */
#define Ix86_loopd	110	/* */
#define Ix86_loopq 	111
#define Ix86_loopwe	112	/* */
#define Ix86_loope	113	/* */
#define Ix86_loopde	114	/* */
#define Ix86_loopqe 	115
#define Ix86_loopwne	116	/* */
#define Ix86_loopne	117	/* */
#define Ix86_loopdne	118	/* */
#define Ix86_loopqne 	119
#define Ix86_lsl	120	/* */
#define Ix86_ltr	121	/* */
#define Ix86_mov	122
#define Ix86_movsp	123 /* ??? */
#define Ix86_movs	124
#define Ix86_movsx	125
#define Ix86_movzx	126
#define Ix86_mul	127
#define Ix86_neg	128
#define Ix86_nop	129
#define Ix86_not	130
#define Ix86_or		131
#define Ix86_out	132	/* */
#define Ix86_outs	133	/* */
#define Ix86_pop	134
#define Ix86_popaw	135	/* */
#define Ix86_popa	136
#define Ix86_popad	137	/* */
#define Ix86_popaq 	138
#define Ix86_popfw	139	/* */
#define Ix86_popf	140
#define Ix86_popfd	141	/* */
#define Ix86_popfq 	142
#define Ix86_push	143
#define Ix86_pushaw	144	/* */
#define Ix86_pusha	145
#define Ix86_pushad	146	/* */
#define Ix86_pushaq 	147
#define Ix86_pushfw	148	/* */
#define Ix86_pushf	149
#define Ix86_pushfd	150	/* */
#define Ix86_pushfq 	151
#define Ix86_rcl	152
#define Ix86_rcr	153
#define Ix86_rol	154
#define Ix86_ror	155
#define Ix86_rep	156
#define Ix86_repe	157
#define Ix86_repne	158
#define Ix86_ret	159
#define Ix86_retf	160
#define Ix86_sahf	161
#define Ix86_sal	162	/* */
#define Ix86_sar	163
#define Ix86_shl	164
#define Ix86_shr	165
#define Ix86_sbb	166
#define Ix86_scas	167
#define Ix86_seta	168	/* */
#define Ix86_setae	169	/* */
#define Ix86_setb	170
#define Ix86_setbe	171
#define Ix86_setc	172	/* */
#define Ix86_sete	173	/* */
#define Ix86_setg	174	/* */
#define Ix86_setge	175	/* */
#define Ix86_setl	176
#define Ix86_setle	177
#define Ix86_setna	178	/* */
#define Ix86_setnae	179	/* */
#define Ix86_setnb	180
#define Ix86_setnbe	181
#define Ix86_setnc	182	/* */
#define Ix86_setne	183	/* */
#define Ix86_setng	184	/* */
#define Ix86_setnge	185	/* */
#define Ix86_setnl	186
#define Ix86_setnle	187
#define Ix86_setno	188
#define Ix86_setnp	189
#define Ix86_setns	190
#define Ix86_setnz	191
#define Ix86_seto	192
#define Ix86_setp	193
#define Ix86_setpe	194	/* */
#define Ix86_setpo	195	/* */
#define Ix86_sets	196
#define Ix86_setz	197
#define Ix86_sgdt	198	/* */
#define Ix86_sidt	199	/* */
#define Ix86_shld	200
#define Ix86_shrd	201
#define Ix86_sldt	202	/* */
#define Ix86_smsw	203	/* */
#define Ix86_stc	204
#define Ix86_std	205
#define Ix86_sti	206
#define Ix86_stos	207
#define Ix86_str	208	/* */
#define Ix86_sub	209
#define Ix86_test	210
#define Ix86_verr	211
#define Ix86_verw	212
#define Ix86_wait	213
#define Ix86_xchg	214
#define Ix86_xlat	215
#define Ix86_xor	216
#define Ix86_cmpxchg	217
#define Ix86_bswap	218

/* not verified */
#define Ix86_xadd	219
#define Ix86_invd	220
#define Ix86_wbinvd	221
#define Ix86_invlpg	222
#define Ix86_rdmsr	223
#define Ix86_wrmsr	224
#define Ix86_cpuid	225
#define Ix86_cmpxchg8b	226
#define Ix86_rdtsc	227
#define Ix86_rsm	228
#define Ix86_cmova	229
#define Ix86_cmovb	230
#define Ix86_cmovbe	231
#define Ix86_cmovg	232
#define Ix86_cmovge	233
#define Ix86_cmovl	234
#define Ix86_cmovle	235
#define Ix86_cmovnb	236
#define Ix86_cmovno	237
#define Ix86_cmovnp	238
#define Ix86_cmovns	239
#define Ix86_cmovnz	240
#define Ix86_cmovo	241
#define Ix86_cmovp	242
#define Ix86_cmovs	243
#define Ix86_cmovz	244

/* for floating point */
#define Ix86_fcmovb	245
#define Ix86_fcmove	246
#define Ix86_fcmovbe	247
#define Ix86_fcmovu	248
#define Ix86_fcmovnb	249
#define Ix86_fcmovne	250
#define Ix86_fcmovnbe	251
#define Ix86_fcmovnu	252
#define Ix86_fcomi	253
#define Ix86_fucomi	254
#define Ix86_fcomip	255
#define Ix86_fucomip	256
#define Ix86_rdpmc	257
#define Ix86_fld	258
#define Ix86_fst	259
#define Ix86_fstp	260
#define Ix86_fxch	261
#define Ix86_fild	262
#define Ix86_fist	263
#define Ix86_fistp	264
#define Ix86_fbld	265	/* */
#define Ix86_fbstp	266	/* */
#define Ix86_fadd	267
#define Ix86_faddp	268
#define Ix86_fiadd	269
#define Ix86_fsub	270
#define Ix86_fsubp	271
#define Ix86_fisub	272
#define Ix86_fsubr	273
#define Ix86_fsubrp	274
#define Ix86_fisubr	275
#define Ix86_fmul	276
#define Ix86_fmulp	277
#define Ix86_fimul	278
#define Ix86_fdiv	279
#define Ix86_fdivp	280
#define Ix86_fidiv	281
#define Ix86_fdivr	282
#define Ix86_fdivrp	283
#define Ix86_fidivr	284
#define Ix86_fsqrt	285
#define Ix86_fscale	286
#define Ix86_fprem	287
#define Ix86_frndint	288
#define Ix86_fxtract	289	/* */
#define Ix86_fabs	290
#define Ix86_fchs	291
#define Ix86_fcom	292
#define Ix86_fcomp	293
#define Ix86_fcompp	294
#define Ix86_ficom	295
#define Ix86_ficomp	296
#define Ix86_ftst	297
#define Ix86_fxam	298	/* */
#define Ix86_fptan	299
#define Ix86_fpatan	300
#define Ix86_f2xm1	301
#define Ix86_fyl2x	302
#define Ix86_fyl2xp1	303
#define Ix86_fldz	304
#define Ix86_fld1	305
#define Ix86_fldpi	306
#define Ix86_fldl2t	307
#define Ix86_fldl2e	308
#define Ix86_fldlg2	309
#define Ix86_fldln2	310
#define Ix86_finit	311
#define Ix86_fninit	312
#define Ix86_fsetpm	313
#define Ix86_fldcw	314
#define Ix86_fstcw	315
#define Ix86_fnstcw	316
#define Ix86_fstsw	317
#define Ix86_fnstsw	318
#define Ix86_fclex	319
#define Ix86_fnclex	320
#define Ix86_fstenv	321
#define Ix86_fnstenv	322
#define Ix86_fldenv	323
#define Ix86_fsave	324
#define Ix86_fnsave	325
#define Ix86_frstor	326
#define Ix86_fincstp	327
#define Ix86_fdecstp	328
#define Ix86_ffree	329
#define Ix86_fnop	330
#define Ix86_feni	331
#define Ix86_fneni	332
#define Ix86_fdisi	333
#define Ix86_fndisi	334
#define Ix86_fprem1	335
#define Ix86_fsincos	336
#define Ix86_fsin	337
#define Ix86_fcos	338
#define Ix86_fucom	339
#define Ix86_fucomp	340
#define Ix86_fucompp	341

#define Ix86_setalc	342
#define Ix86_svdc	343
#define Ix86_rsdc	344
#define Ix86_svldt	345
#define Ix86_rsldt	346
#define Ix86_svts	347
#define Ix86_rsts	348
#define Ix86_icebp	349
#define Ix86_loadall	350
#define Ix86_emms	351
#define Ix86_movd	352
#define Ix86_movq	353
#define Ix86_packsswb	354
#define Ix86_packssdw	355
#define Ix86_packuswb	356
#define Ix86_paddb	357
#define Ix86_paddw	358
#define Ix86_paddd	359
#define Ix86_paddsb	360
#define Ix86_paddsw	361
#define Ix86_paddusb	362
#define Ix86_paddusw	363
#define Ix86_pand	364
#define Ix86_pandn	365
#define Ix86_pcmpeqb	366
#define Ix86_pcmpeqw	367
#define Ix86_pcmpeqd	368
#define Ix86_pcmpgtb	369
#define Ix86_pcmpgtw	370
#define Ix86_pcmpgtd	371
#define Ix86_pmaddwd	372
#define Ix86_pmulhw	373
#define Ix86_pmullw	374
#define Ix86_por	375
#define Ix86_psllw	376
#define Ix86_pslld	377
#define Ix86_psllq	378
#define Ix86_psraw	379
#define Ix86_psrad	380
#define Ix86_psrlw	381
#define Ix86_psrld	382
#define Ix86_psrlq	383
#define Ix86_psubb	384
#define Ix86_psubw	385
#define Ix86_psubd	386
#define Ix86_psubsb	387
#define Ix86_psubsw	388
#define Ix86_psubusb	389
#define Ix86_psubusw	390
#define Ix86_punpckhbw	391
#define Ix86_punpckhwd	392
#define Ix86_punpckhdq	393
#define Ix86_punpcklbw	394
#define Ix86_punpcklwd	395
#define Ix86_punpckldq	396
#define Ix86_pxor	397
#define Ix86_fxsave	398
#define Ix86_fxrstor	399
#define Ix86_sysenter	400
#define Ix86_sysexit	401
#define Ix86_pavgusb	402
#define Ix86_pfadd	403
#define Ix86_pfsub	404
#define Ix86_pfsubr	405
#define Ix86_pfacc	406
#define Ix86_pfcmpge	407
#define Ix86_pfcmpgt	408
#define Ix86_pfcmpeq	409
#define Ix86_pfmin	410
#define Ix86_pfmax	411
#define Ix86_pi2fd	412
#define Ix86_pf2id	413
#define Ix86_pfrcp	414
#define Ix86_pfrsqrt	415
#define Ix86_pfmul	416
#define Ix86_pfrcpit1	417
#define Ix86_pfrsqit1	418
#define Ix86_pfrcpit2	419
#define Ix86_pmulhrw	420
#define Ix86_femms	421
#define Ix86_prefetch	422
#define Ix86_prefetchw	423
#define Ix86_addps	424
#define Ix86_addss	425
#define Ix86_andnps	426
#define Ix86_andps	427
#define Ix86_cmpps	428
#define Ix86_cmpss	429
#define Ix86_comiss	430
#define Ix86_cvtpi2ps	431
#define Ix86_cvtps2pi	432
#define Ix86_cvtsi2ss	433
#define Ix86_cvtss2si	434
#define Ix86_cvttps2pi	435
#define Ix86_cvttss2si	436
#define Ix86_divps	437
#define Ix86_divss	438
#define Ix86_ldmxcsr	439
#define Ix86_maxps	440
#define Ix86_maxss	441
#define Ix86_minps	442
#define Ix86_minss	443
#define Ix86_movaps	444
#define Ix86_movhlps	445
#define Ix86_movhps	446
#define Ix86_movlhps	447
#define Ix86_movlps	448
#define Ix86_movmskps	449
#define Ix86_movss	450
#define Ix86_movups	451
#define Ix86_mulps	452
#define Ix86_mulss	453
#define Ix86_orps	454
#define Ix86_rcpps	455
#define Ix86_rcpss	456
#define Ix86_rsqrtps	457
#define Ix86_rsqrtss	458
#define Ix86_shufps	459
#define Ix86_sqrtps	460
#define Ix86_sqrtss	461
#define Ix86_stmxcsr	462
#define Ix86_subps	463
#define Ix86_subss	464
#define Ix86_ucomiss	465
#define Ix86_unpckhps	466
#define Ix86_unpcklps	467
#define Ix86_xorps	468
#define Ix86_pavgb	469
#define Ix86_pavgw	470
#define Ix86_pextrw	471
#define Ix86_pinsrw	472
#define Ix86_pmaxsw	473
#define Ix86_pmaxub	474
#define Ix86_pminsw	475
#define Ix86_pminub	476
#define Ix86_pmovmskb	477
#define Ix86_pmulhuw	478
#define Ix86_psadbw	479
#define Ix86_pshufw	480
#define Ix86_maskmovq	481
#define Ix86_movntps	482
#define Ix86_movntq	483
#define Ix86_prefetcht0	484
#define Ix86_prefetcht1	485
#define Ix86_prefetcht2	486
#define Ix86_prefetchnta	487
#define Ix86_sfence	488
#define Ix86_cmpeqps	489
#define Ix86_cmpltps	490
#define Ix86_cmpleps	491
#define Ix86_cmpunordps	492
#define Ix86_cmpneqps	493
#define Ix86_cmpnltps	494
#define Ix86_cmpnleps	495
#define Ix86_cmpordps	496
#define Ix86_cmpeqss	497
#define Ix86_cmpltss	498
#define Ix86_cmpless	499
#define Ix86_cmpunordss	500
#define Ix86_cmpneqss	501
#define Ix86_cmpnltss	502
#define Ix86_cmpnless	503
#define Ix86_cmpordss	504
/* for IDA 4.70 */
#define Ix86_pf2iw 	505
#define Ix86_pfnacc 	506
#define Ix86_pfpnacc 	507
#define Ix86_pi2fw 	508
#define Ix86_pswapd 	509
#define Ix86_fstp1 	510
#define Ix86_fcom2 	511
#define Ix86_fcomp3 	512
#define Ix86_fxch4 	513
#define Ix86_fcomp5 	514
#define Ix86_ffreep 	515
#define Ix86_fxch7 	516
#define Ix86_fstp8 	517
#define Ix86_fstp9 	518
/* P4 instructions */
#define Ix86_addpd 	519
#define Ix86_addsd 	520
#define Ix86_andnpd 	521
#define Ix86_andpd 	522
#define Ix86_clflush 	523
#define Ix86_cmppd 	524
#define Ix86_cmpsd 	525
#define Ix86_comisd 	526
#define Ix86_cvtdq2pd	527
#define Ix86_cvtdq2ps 	528
#define Ix86_cvtpd2dq 	529
#define Ix86_cvtpd2pi 	530
#define Ix86_cvtpd2ps 	531
#define Ix86_cvtpi2pd 	532
#define Ix86_cvtps2dq 	533
#define Ix86_cvtps2pd 	534
#define Ix86_cvtsd2si 	535
#define Ix86_cvtsd2ss 	536
#define Ix86_cvtsi2sd 	537
#define Ix86_cvtss2sd 	538
#define Ix86_cvttpd2dq 	539
#define Ix86_cvttpd2pi  540
#define Ix86_cvttps2dq  541
#define Ix86_cvttsd2si  542
#define Ix86_divpd 	543
#define Ix86_divsd 	544
#define Ix86_lfence 	545
#define Ix86_maskmovdqu 546
#define Ix86_maxpd 	547
#define Ix86_maxsd 	548
#define Ix86_mfence 	549
#define Ix86_minpd 	550
#define Ix86_minsd 	551
#define Ix86_movapd 	552
#define Ix86_movdq2q 	553
#define Ix86_movdqa 	554
#define Ix86_movdqu 	555
#define Ix86_movhpd 	556
#define Ix86_movlpd 	557
#define Ix86_movmskpd 	558
#define Ix86_movntdq 	559
#define Ix86_movnti 	560
#define Ix86_movntpd 	561
#define Ix86_movq2dq 	562
#define Ix86_movsd 	563
#define Ix86_movupd 	564
#define Ix86_mulpd 	565
#define Ix86_mulsd 	566
#define Ix86_orpd 	567
#define Ix86_paddq 	568
#define Ix86_pause 	569
#define Ix86_pmuludq 	570
#define Ix86_pshufd 	571
#define Ix86_pshufhw 	572
#define Ix86_pshuflw 	573
#define Ix86_pslldq 	574
#define Ix86_psrldq 	575
#define Ix86_psubq 	576
#define Ix86_punpckhqdq 577
#define Ix86_punpcklqdq 578
#define Ix86_shufpd 	579
#define Ix86_sqrtpd 	580
#define Ix86_sqrtsd 	581
#define Ix86_subpd 	582
#define Ix86_subsd 	583
#define Ix86_ucomisd 	584
#define Ix86_unpckhpd 	585
#define Ix86_unpcklpd 	586
#define Ix86_xorpd 	587
#define Ix86_syscall 	588
#define Ix86_sysret 	589
#define Ix86_swapgs 	590
#define Ix86_movddup	591
#define Ix86_movshdup	592
#define Ix86_movsldup	593
/* amd64 */
#define Ix86_movsxd	594
#define Ix86_cmpxchg16b	595
/* sse3 */
#define Ix86_addsubpd	596
#define Ix86_addsubps   597
#define Ix86_haddpd	598
#define Ix86_haddps	599
#define Ix86_hsubpd	600
#define Ix86_hsubps	601
#define Ix86_monitor	602
#define Ix86_mwait	603
#define Ix86_fisttp	604
#define Ix86_lddqu	605
/* SSSE3 */
#define Ix86_psignb	606
#define Ix86_psignw	607
#define Ix86_psignd	608
#define Ix86_pshufb	609
#define Ix86_pmulhrsw	610
#define Ix86_pmaddubsw	611
#define Ix86_phsubsw	612
#define Ix86_phaddsw	613
#define Ix86_phaddw	614
#define Ix86_phaddd	615
#define Ix86_phsubw	616
#define Ix86_phsubd	617
#define Ix86_palignr	618
#define Ix86_pabsb	619
#define Ix86_pabsw	620
#define Ix86_pabsd	621
/* VMX */
#define Ix86_vmcall	622
#define Ix86_vmclear	623
#define Ix86_vmlaunch	624
#define Ix86_vmresume	625
#define Ix86_vmptrld	626
#define Ix86_vmptrst	627
#define Ix86_vmread	628
#define Ix86_vmwrite	629
#define Ix86_vmxoff	630
#define Ix86_vmxon	631
#define Ix86_ud2	632
#define Ix86_rdtscp	633
#define Ix86_pfrcpv	634
#define Ix86_pfrsqrtv	635
/* sse2 pseudo */
#define Ix86_cmpeqpd	636
#define Ix86_cmpltpd	637
#define Ix86_cmplepd	638
#define Ix86_cmpunordpd	639
#define Ix86_cmpneqpd	640
#define Ix86_cmpnltpd	641
#define Ix86_cmpnlepd	642
#define Ix86_cmpordpd	643
#define Ix86_cmpeqsd	644
#define Ix86_cmpltsd	645
#define Ix86_cmplesd	646
#define Ix86_cmpunordsd	647
#define Ix86_cmpneqsd	648
#define Ix86_cmpnltsd	649
#define Ix86_cmpnlesd	650
#define Ix86_cmpordsd	651
/* SSSE4.1 */
#define Ix86_blendpd	652
#define Ix86_blendps	653
#define Ix86_blendvpd	654
#define Ix86_blendvps	655
#define Ix86_dppd	656
#define Ix86_dpps	657
#define Ix86_extractps	658
#define Ix86_insertps	659
#define Ix86_movntdqa	660
#define Ix86_mpsadbw	661
#define Ix86_packusdw	662
#define Ix86_pblendvb	663
#define Ix86_pblendw	664
#define Ix86_pcmpeqq	665
#define Ix86_pextrb	666
#define Ix86_pextrd	667
#define Ix86_pextrq	668
#define Ix86_phminposuw	669
#define Ix86_pinsrb	670
#define Ix86_pinsrd	671
#define Ix86_pinsrq	672
#define Ix86_pmaxsb	673
#define Ix86_pmaxsd	674
#define Ix86_pmaxud	675
#define Ix86_pmaxuw	676
#define Ix86_pminsb	677
#define Ix86_pminsd	678
#define Ix86_pminud	679
#define Ix86_pminuw	680
#define Ix86_pmovsxbw	681
#define Ix86_pmovsxbd	682
#define Ix86_pmovsxbq	683
#define Ix86_pmovsxwd	684
#define Ix86_pmovsxwq	685
#define Ix86_pmovsxdq	686
#define Ix86_pmovzxbw	687
#define Ix86_pmovzxbd	688
#define Ix86_pmovzxbq	689
#define Ix86_pmovzxwd	690
#define Ix86_pmovzxwq	691
#define Ix86_pmovzxdq	692
#define Ix86_pmuldq	693
#define Ix86_pmulld	694
#define Ix86_ptest	695
#define Ix86_roundpd	696
#define Ix86_roundps	697
#define Ix86_roundsd	698
#define Ix86_roundss	699
/* SSSE4.2 */
#define Ix86_crc32	700
#define Ix86_pcmpestri	701
#define Ix86_pcmpestrm	702
#define Ix86_pcmpistri	703
#define Ix86_pcmpistrm	704
#define Ix86_pcmpgtq	705
#define Ix86_popcnt	706
#define Ix86_extrq	707
#define Ix86_insertq	708
#define Ix86_movntsd	709
#define Ix86_movntss	710
#define Ix86_lzcnt	711
#define Ix86_xgetbv	712
#define Ix86_xrstor	713
#define Ix86_xsave	714
#define Ix86_xsetbv	715
#define Ix86_getsec	716
#define Ix86_clgi	717
#define Ix86_invlpga	718
#define Ix86_skinit	719
#define Ix86_stgi	720
#define Ix86_vmexit	721
#define Ix86_vmload	722
#define Ix86_vmmcall	723
#define Ix86_vmrun	724
#define Ix86_vmsave	725
#define Ix86_invept	726
#define Ix86_invvpid	727
#define Ix86_movbe	728
#define Ix86_aesenc	729
#define Ix86_aesenclast	730
#define Ix86_aesdec	731
#define Ix86_aesdeclast	732
#define Ix86_aesimc	733
#define Ix86_aeskeygenassist	734
#define Ix86_pclmulqdq	735
/* x86 registers for 32bit mode */
#define r_EAX	0
#define r_ECX	1
#define r_EDX	2
#define r_EBX	3
#define r_ESP	4
#define r_EBP	5
#define r_ESI	6
#define r_EDI	7

#define r_RAX	0
#define r_RCX	1
#define r_RDX	2
#define r_RBX	3
#define r_RSP	4
#define r_RBP	5
#define r_RSI	6
#define r_RDI	7

/* from IDA 4.70 */
#define r_R8	8
#define r_R9	9
#define r_R10	10
#define r_R11	11
#define r_R12	12
#define r_R13	13
#define r_R14	14
#define r_R15	15

#define r_AL	16
#define r_AH	20
#define r_CL	17
#define r_CH	21
#define r_DL	18
#define r_DH	22
#define r_BL	19
#define r_BH	23

/* some strange registers */
#define r_SPL	24
#define r_BPL	25
#define r_SIL	26
#define r_DIL	27

/* segment registers */
#define r_EIP	28
#define r_ES	29
#define r_CS	30
#define r_SS	31
#define r_DS	32
#define r_FS	33
#define r_GS	34

/* enum & struct definition */
/* instruction types */
#define IT_ORINARY	0
#define FPU		1
#define MMX		2
#define AMD_3D		3
#define SSE		4
#define SSE3		5
#define SSSE3		6
#define UNKNOWN_IT	7

/* for processor from which instruction may be recognized */
#define FROM_486	1
#define FROM_P		2
#define FROM_PPRO	3
#define FROM_PII	4
#define FROM_P4		5
#define UNKNOWN		0xff

/* flags - as they located in (E)FLAGS reg */
#define f_CF	1
#define f_PF	(1<<2)
#define f_AF	(1<<4)
#define f_ZF	(1<<6)
#define f_SF	(1<<7)
#define f_TF	(1<<8)
#define f_IF	(1<<9)
#define f_DF	(1<<10)
#define f_OF	(1<<11)

/* main problem */
struct RP_opcode {
 unsigned char type;
 unsigned char from_proc;
 unsigned __int64 regs;
 unsigned short cflags;
 unsigned short rflags;
 unsigned short uflags;
 char ops;
};

extern 
#ifdef __cplusplus
"C"
#endif
const struct RP_opcode *const RP_data[];

#endif /* RP_X86_INCLUDED */