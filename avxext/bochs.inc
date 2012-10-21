enum avx_insn_type_t
{
 AVX_vaddpd = CUSTOM_CMD_ITYPE,
 AVX_vaddps,
 AVX_vaddsd,
 AVX_vaddss,
 AVX_vaddsubpd,
 AVX_vaddsubps,
 AVX_vaesdec,
 AVX_vaesdeclast,
 AVX_vaesenc,
 AVX_vaesenclast,
 AVX_vaesimc,
 AVX_vaeskeygenassist,
 AVX_vandnpd,
 AVX_vandnps,
 AVX_vandpd,
 AVX_vandps,
 AVX_vblendpd,
 AVX_vblendps,
 AVX_vblendvpd,
 AVX_vblendvps,
 AVX_vbroadcastf128,
 AVX_vbroadcasti128,
 AVX_vbroadcastsd,
 AVX_vbroadcastss,
 AVX_vcmppd,
 AVX_vcmpps,
 AVX_vcmpsd,
 AVX_vcmpss,
 AVX_vcomisd,
 AVX_vcomiss,
 AVX_vcvtdq2pd,
 AVX_vcvtdq2ps,
 AVX_vcvtpd2dq,
 AVX_vcvtpd2ps,
 AVX_vcvtph2ps,
 AVX_vcvtps2dq,
 AVX_vcvtps2pd,
 AVX_vcvtps2ph,
 AVX_vcvtsd2si,
 AVX_vcvtsd2ss,
 AVX_vcvtsi2sd,
 AVX_vcvtsi2ss,
 AVX_vcvtss2sd,
 AVX_vcvtss2si,
 AVX_vcvttpd2dq,
 AVX_vcvttps2dq,
 AVX_vcvttsd2si,
 AVX_vcvttss2si,
 AVX_vdivpd,
 AVX_vdivps,
 AVX_vdivsd,
 AVX_vdivss,
 AVX_vdppd,
 AVX_vdpps,
 AVX_vextractf128,
 AVX_vextracti128,
 AVX_vextractps,
 AVX_vfmadd132pd,
 AVX_vfmadd132ps,
 AVX_vfmadd132sd,
 AVX_vfmadd132ss,
 AVX_vfmadd213pd,
 AVX_vfmadd213ps,
 AVX_vfmadd213sd,
 AVX_vfmadd213ss,
 AVX_vfmadd231pd,
 AVX_vfmadd231ps,
 AVX_vfmadd231sd,
 AVX_vfmadd231ss,
 AVX_vfmaddsub132pd,
 AVX_vfmaddsub132ps,
 AVX_vfmaddsub213pd,
 AVX_vfmaddsub213ps,
 AVX_vfmaddsub231pd,
 AVX_vfmaddsub231ps,
 AVX_vfmsub132pd,
 AVX_vfmsub132ps,
 AVX_vfmsub132sd,
 AVX_vfmsub132ss,
 AVX_vfmsub213pd,
 AVX_vfmsub213ps,
 AVX_vfmsub213sd,
 AVX_vfmsub213ss,
 AVX_vfmsub231pd,
 AVX_vfmsub231ps,
 AVX_vfmsub231sd,
 AVX_vfmsub231ss,
 AVX_vfmsubadd132pd,
 AVX_vfmsubadd132ps,
 AVX_vfmsubadd213pd,
 AVX_vfmsubadd213ps,
 AVX_vfmsubadd231pd,
 AVX_vfmsubadd231ps,
 AVX_vfnmadd132pd,
 AVX_vfnmadd132ps,
 AVX_vfnmadd132sd,
 AVX_vfnmadd132ss,
 AVX_vfnmadd213pd,
 AVX_vfnmadd213ps,
 AVX_vfnmadd213sd,
 AVX_vfnmadd213ss,
 AVX_vfnmadd231pd,
 AVX_vfnmadd231ps,
 AVX_vfnmadd231sd,
 AVX_vfnmadd231ss,
 AVX_vfnmsub132pd,
 AVX_vfnmsub132ps,
 AVX_vfnmsub132sd,
 AVX_vfnmsub132ss,
 AVX_vfnmsub213pd,
 AVX_vfnmsub213ps,
 AVX_vfnmsub213sd,
 AVX_vfnmsub213ss,
 AVX_vfnmsub231pd,
 AVX_vfnmsub231ps,
 AVX_vfnmsub231sd,
 AVX_vfnmsub231ss,
 AVX_vgatherdd,
 AVX_vgatherdpd,
 AVX_vgatherdps,
 AVX_vgatherdq,
 AVX_vgatherqd,
 AVX_vgatherqpd,
 AVX_vgatherqps,
 AVX_vgatherqq,
 AVX_vhaddpd,
 AVX_vhaddps,
 AVX_vhsubpd,
 AVX_vhsubps,
 AVX_vinsertf128,
 AVX_vinserti128,
 AVX_vinsertps,
 AVX_vlddqu,
 AVX_vldmxcsr,
 AVX_vmaskmovd1,
 AVX_vmaskmovd2,
 AVX_vmaskmovdqu,
 AVX_vmaskmovpd1,
 AVX_vmaskmovpd2,
 AVX_vmaskmovps1,
 AVX_vmaskmovps2,
 AVX_vmaskmovq1,
 AVX_vmaskmovq2,
 AVX_vmaxpd,
 AVX_vmaxps,
 AVX_vmaxsd,
 AVX_vmaxss,
 AVX_vminpd,
 AVX_vminps,
 AVX_vminsd,
 AVX_vminss,
 AVX_vmovapd1,
 AVX_vmovapd2,
 AVX_vmovaps1,
 AVX_vmovaps2,
 AVX_vmovd1,
 AVX_vmovd2,
 AVX_vmovddup,
 AVX_vmovdqa1,
 AVX_vmovdqa2,
 AVX_vmovdqu1,
 AVX_vmovdqu2,
 AVX_vmovhlpd,
 AVX_vmovhlps,
 AVX_vmovhpd1,
 AVX_vmovhpd2,
 AVX_vmovhps1,
 AVX_vmovhps2,
 AVX_vmovlhpd,
 AVX_vmovlhps,
 AVX_vmovlpd1,
 AVX_vmovlpd2,
 AVX_vmovlps1,
 AVX_vmovlps2,
 AVX_vmovmskpd,
 AVX_vmovmskps,
 AVX_vmovntdq,
 AVX_vmovntdqa,
 AVX_vmovntpd,
 AVX_vmovntps,
 AVX_vmovq1,
 AVX_vmovq2,
 AVX_vmovq3,
 AVX_vmovq4,
 AVX_vmovsd1,
 AVX_vmovsd2,
 AVX_vmovshdup,
 AVX_vmovsldup,
 AVX_vmovss1,
 AVX_vmovss2,
 AVX_vmovupd1,
 AVX_vmovupd2,
 AVX_vmovups1,
 AVX_vmovups2,
 AVX_vmpsadbw,
 AVX_vmulpd,
 AVX_vmulps,
 AVX_vmulsd,
 AVX_vmulss,
 AVX_vorpd,
 AVX_vorps,
 AVX_vpabsb,
 AVX_vpabsd,
 AVX_vpabsw,
 AVX_vpackssdw,
 AVX_vpacksswb,
 AVX_vpackusdw,
 AVX_vpackuswb,
 AVX_vpaddb,
 AVX_vpaddd,
 AVX_vpaddq,
 AVX_vpaddsb,
 AVX_vpaddsw,
 AVX_vpaddusb,
 AVX_vpaddusw,
 AVX_vpaddw,
 AVX_vpalignr,
 AVX_vpand,
 AVX_vpandn,
 AVX_vpavgb,
 AVX_vpavgw,
 AVX_vpblendd,
 AVX_vpblendvb,
 AVX_vpblendw,
 AVX_vpbroadcastb,
 AVX_vpbroadcastd,
 AVX_vpbroadcastq,
 AVX_vpbroadcastw,
 AVX_vpclmulqdq,
 AVX_vpcmpeqb,
 AVX_vpcmpeqd,
 AVX_vpcmpeqq,
 AVX_vpcmpeqw,
 AVX_vpcmpestri,
 AVX_vpcmpestrm,
 AVX_vpcmpgtb,
 AVX_vpcmpgtd,
 AVX_vpcmpgtq,
 AVX_vpcmpgtw,
 AVX_vpcmpistri,
 AVX_vpcmpistrm,
 AVX_vperm2f128,
 AVX_vperm2128,
 AVX_vpermd,
 AVX_vpermilpd1,
 AVX_vpermilpd2,
 AVX_vpermilps1,
 AVX_vpermilps2,
 AVX_vpermpd,
 AVX_vpermps,
 AVX_vpermq,
 AVX_vpextrb,
 AVX_vpextrd,
 AVX_vpextrq,
 AVX_vpextrw1,
 AVX_vpextrw2,
 AVX_vphaddd,
 AVX_vphaddsw,
 AVX_vphaddw,
 AVX_vphminposuw,
 AVX_vphsubd,
 AVX_vphsubsw,
 AVX_vphsubw,
 AVX_vpinsrb,
 AVX_vpinsrd,
 AVX_vpinsrq,
 AVX_vpinsrw,
 AVX_vpmaddubsw,
 AVX_vpmaddwd,
 AVX_vpmaxsb,
 AVX_vpmaxsd,
 AVX_vpmaxsw,
 AVX_vpmaxub,
 AVX_vpmaxud,
 AVX_vpmaxuw,
 AVX_vpminsb,
 AVX_vpminsd,
 AVX_vpminsw,
 AVX_vpminub,
 AVX_vpminud,
 AVX_vpminuw,
 AVX_vpmovmskb,
 AVX_vpmovsxbd,
 AVX_vpmovsxbq,
 AVX_vpmovsxbw,
 AVX_vpmovsxdq,
 AVX_vpmovsxwd,
 AVX_vpmovsxwq,
 AVX_vpmovzxbd,
 AVX_vpmovzxbq,
 AVX_vpmovzxbw,
 AVX_vpmovzxdq,
 AVX_vpmovzxwd,
 AVX_vpmovzxwq,
 AVX_vpmuldq,
 AVX_vpmulhrsw,
 AVX_vpmulhuw,
 AVX_vpmulhw,
 AVX_vpmulld,
 AVX_vpmullw,
 AVX_vpmuludq,
 AVX_vpor,
 AVX_vpsadbw,
 AVX_vpshufb,
 AVX_vpshufd,
 AVX_vpshufhw,
 AVX_vpshuflw,
 AVX_vpsignb,
 AVX_vpsignd,
 AVX_vpsignw,
 AVX_vpslld1,
 AVX_vpslld2,
 AVX_vpslldq,
 AVX_vpsllq1,
 AVX_vpsllq2,
 AVX_vpsllvd,
 AVX_vpsllvq,
 AVX_vpsllw1,
 AVX_vpsllw2,
 AVX_vpsrad1,
 AVX_vpsrad2,
 AVX_vpsravd,
 AVX_vpsraw1,
 AVX_vpsraw2,
 AVX_vpsrld1,
 AVX_vpsrld2,
 AVX_vpsrldq,
 AVX_vpsrlq1,
 AVX_vpsrlq2,
 AVX_vpsrlvd,
 AVX_vpsrlvq,
 AVX_vpsrlw1,
 AVX_vpsrlw2,
 AVX_vpsubb,
 AVX_vpsubd,
 AVX_vpsubq,
 AVX_vpsubsb,
 AVX_vpsubsw,
 AVX_vpsubusb,
 AVX_vpsubusw,
 AVX_vpsubw,
 AVX_vptest,
 AVX_vpunpckhbw,
 AVX_vpunpckhdq,
 AVX_vpunpckhqdq,
 AVX_vpunpckhwd,
 AVX_vpunpcklbw,
 AVX_vpunpckldq,
 AVX_vpunpcklqdq,
 AVX_vpunpcklwd,
 AVX_vpxor,
 AVX_vrcpps,
 AVX_vrcpss,
 AVX_vroundpd,
 AVX_vroundps,
 AVX_vroundsd,
 AVX_vroundss,
 AVX_vrsqrtps,
 AVX_vrsqrtss,
 AVX_vshufpd,
 AVX_vshufps,
 AVX_vsqrtpd,
 AVX_vsqrtps,
 AVX_vsqrtsd,
 AVX_vsqrtss,
 AVX_vstmxcsr,
 AVX_vsubpd,
 AVX_vsubps,
 AVX_vsubsd,
 AVX_vsubss,
 AVX_vtestpd,
 AVX_vtestps,
 AVX_vucomisd,
 AVX_vucomiss,
 AVX_vunpckhpd,
 AVX_vunpckhps,
 AVX_vunpcklpd,
 AVX_vunpcklps,
 AVX_vxorpd,
 AVX_vxorps,
 AVX_vzeroall,
 AVX_vzeroupper,
 AVX_frczpd,
 AVX_frczps,
 AVX_frczsd,
 AVX_frczss,
 AVX_vpcmov1,
 AVX_vpcmov2,
 AVX_vpcomb,
 AVX_vpcomd,
 AVX_vpcomq,
 AVX_vpcomub,
 AVX_vpcomud,
 AVX_vpcomuq,
 AVX_vpcomuw,
 AVX_vpcomw,
 AVX_vphaddbd,
 AVX_vphaddbq,
 AVX_vphaddbw,
 AVX_vphadddq,
 AVX_vphaddubd,
 AVX_vphaddubq,
 AVX_vphaddubw,
 AVX_vphaddudq,
 AVX_vphadduwd,
 AVX_vphadduwq,
 AVX_vphaddwd,
 AVX_vphaddwq,
 AVX_vphsubbw,
 AVX_vphsubdq,
 AVX_vphsubwd,
 AVX_vpmacsdd,
 AVX_vpmacsdqh,
 AVX_vpmacsdql,
 AVX_vpmacssdd,
 AVX_vpmacssdqh,
 AVX_vpmacssdql,
 AVX_vpmacsswd,
 AVX_vpmacssww,
 AVX_vpmacswd,
 AVX_vpmacsww,
 AVX_vpmadcsswd,
 AVX_vpmadcswd,
 AVX_vpperm1,
 AVX_vpperm2,
 AVX_vprotb1,
 AVX_vprotb2,
 AVX_vprotb3,
 AVX_vprotd1,
 AVX_vprotd2,
 AVX_vprotd3,
 AVX_vprotq1,
 AVX_vprotq2,
 AVX_vprotq3,
 AVX_vprotw1,
 AVX_vprotw2,
 AVX_vprotw3,
 AVX_vpshab1,
 AVX_vpshab2,
 AVX_vpshad1,
 AVX_vpshad2,
 AVX_vpshaq1,
 AVX_vpshaq2,
 AVX_vpshaw1,
 AVX_vpshaw2,
 AVX_vpshlb1,
 AVX_vpshlb2,
 AVX_vpshld1,
 AVX_vpshld2,
 AVX_vpshlq1,
 AVX_vpshlq2,
 AVX_vpshlw1,
 AVX_vpshlw2,
 AVX_andn,
 AVX_bextr1,
 AVX_blsi,
 AVX_blsmsk,
 AVX_blsr,
 AVX_bzhi,
 AVX_mulx,
 AVX_pdep,
 AVX_pext,
 AVX_rorx,
 AVX_sarx,
 AVX_shlx,
 AVX_shrx,
 AVX_tzcntl,
 AVX_tzcntq,
 AVX_tzcntw,
 AVX_vfmaddpd1,
 AVX_vfmaddpd2,
 AVX_vfmaddps1,
 AVX_vfmaddps2,
 AVX_vfmaddsd1,
 AVX_vfmaddsd2,
 AVX_vfmaddss1,
 AVX_vfmaddss2,
 AVX_vfmaddsubpd1,
 AVX_vfmaddsubpd2,
 AVX_vfmaddsubps1,
 AVX_vfmaddsubps2,
 AVX_vfmsubaddpd1,
 AVX_vfmsubaddpd2,
 AVX_vfmsubaddps1,
 AVX_vfmsubaddps2,
 AVX_vfmsubpd1,
 AVX_vfmsubpd2,
 AVX_vfmsubps1,
 AVX_vfmsubps2,
 AVX_vfmsubsd1,
 AVX_vfmsubsd2,
 AVX_vfmsubss1,
 AVX_vfmsubss2,
 AVX_vfnmaddpd1,
 AVX_vfnmaddpd2,
 AVX_vfnmaddps1,
 AVX_vfnmaddps2,
 AVX_vfnmaddsd1,
 AVX_vfnmaddsd2,
 AVX_vfnmaddss1,
 AVX_vfnmaddss2,
 AVX_vfnmsubpd1,
 AVX_vfnmsubpd2,
 AVX_vfnmsubps1,
 AVX_vfnmsubps2,
 AVX_vfnmsubsd1,
 AVX_vfnmsubsd2,
 AVX_vfnmsubss1,
 AVX_vfnmsubss2,
 AVX_bextr2,
 AVX_blcfill,
 AVX_blci,
 AVX_blcic,
 AVX_blcmsk,
 AVX_blcs,
 AVX_blsfill,
 AVX_blsic,
 AVX_t1mskc,
 AVX_tzmsk,
};

// merged AVX & XOP opcodes
const struct BxDisasmOpcodeInfo_t
 Ia_vaddpd_Vpd_Hpd_Wpd = { "vaddpd", AVX_vaddpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vaddps_Vps_Hps_Wps = { "vaddps", AVX_vaddps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vaddsd_Vsd_Hpd_Wsd = { "vaddsd", AVX_vaddsd, Vsd, Hpd, Wsd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vaddss_Vss_Hps_Wss = { "vaddss", AVX_vaddss, Vss, Hps, Wss, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vaddsubpd_Vpd_Hpd_Wpd = { "vaddsubpd", AVX_vaddsubpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vaddsubps_Vps_Hps_Wps = { "vaddsubps", AVX_vaddsubps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vaesdec_Vdq_Hdq_Wdq = { "vaesdec", AVX_vaesdec, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vaesdeclast_Vdq_Hdq_Wdq = { "vaesdeclast", AVX_vaesdeclast, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vaesenc_Vdq_Hdq_Wdq = { "vaesenc", AVX_vaesenc, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vaesenclast_Vdq_Hdq_Wdq = { "vaesenclast", AVX_vaesenclast, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vaesimc_Vdq_Wdq = { "vaesimc", AVX_vaesimc, Vdq, Wdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vaeskeygenassist_Vdq_Wdq_Ib = { "vaeskeygenassist", AVX_vaeskeygenassist, Vdq, Wdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vandnpd_Vpd_Hpd_Wpd = { "vandnpd", AVX_vandnpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vandnps_Vps_Hps_Wps = { "vandnps", AVX_vandnps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vandpd_Vpd_Hpd_Wpd = { "vandpd", AVX_vandpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vandps_Vps_Hps_Wps = { "vandps", AVX_vandps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vblendpd_Vpd_Hpd_Wpd_Ib = { "vblendpd", AVX_vblendpd, Vpd, Hpd, Wpd, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vblendps_Vps_Hps_Wps_Ib = { "vblendps", AVX_vblendps, Vps, Hps, Wps, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vblendvpd_Vpd_Hpd_Wpd_Ib = { "vblendvpd", AVX_vblendvpd, Vpd, Hpd, Wpd, VIb, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vblendvps_Vps_Hps_Wps_Ib = { "vblendvps", AVX_vblendvps, Vps, Hps, Wps, VIb, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vbroadcastf128_Vdq_Mdq = { "vbroadcastf128", AVX_vbroadcastf128, Vdq, Mdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vbroadcasti128_Vdq_Mdq = { "vbroadcasti128", AVX_vbroadcasti128, Vdq, Mdq, XX, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vbroadcastsd_Vpd_Wsd = { "vbroadcastsd", AVX_vbroadcastsd, Vpd, Wsd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vbroadcastss_Vps_Wss = { "vbroadcastss", AVX_vbroadcastss, Vps, Wss, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcmppd_Vpd_Hpd_Wpd_Ib = { "vcmppd", AVX_vcmppd, Vpd, Hpd, Wpd, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcmpps_Vps_Hps_Wps_Ib = { "vcmpps", AVX_vcmpps, Vps, Hps, Wps, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcmpsd_Vsd_Hpd_Wsd_Ib = { "vcmpsd", AVX_vcmpsd, Vsd, Hpd, Wsd, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcmpss_Vss_Hps_Wss_Ib = { "vcmpss", AVX_vcmpss, Vss, Hps, Wss, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcomisd_Vsd_Wsd = { "vcomisd", AVX_vcomisd, Vsd, Wsd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcomiss_Vss_Wss = { "vcomiss", AVX_vcomiss, Vss, Wss, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtdq2pd_Vpd_Wq = { "vcvtdq2pd", AVX_vcvtdq2pd, Vpd, Wq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtdq2ps_Vps_Wdq = { "vcvtdq2ps", AVX_vcvtdq2ps, Vps, Wdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtpd2dq_Vq_Wpd = { "vcvtpd2dq", AVX_vcvtpd2dq, Vq, Wpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtpd2ps_Vps_Wpd = { "vcvtpd2ps", AVX_vcvtpd2ps, Vps, Wpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtph2ps_Vps_Wq = { "vcvtph2ps", AVX_vcvtph2ps, Vps, Wq, XX, XX, IA_AVX_F16C };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtps2dq_Vdq_Wps = { "vcvtps2dq", AVX_vcvtps2dq, Vdq, Wps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtps2pd_Vpd_Wps = { "vcvtps2pd", AVX_vcvtps2pd, Vpd, Wps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtps2ph_Wq_Vps_Ib = { "vcvtps2ph", AVX_vcvtps2ph, Wq, Vps, Ib, XX, IA_AVX_F16C };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtsd2si_Gy_Wsd = { "vcvtsd2si", AVX_vcvtsd2si, Gy, Wsd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtsd2ss_Vss_Hps_Wsd = { "vcvtsd2ss", AVX_vcvtsd2ss, Vss, Hps, Wsd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtsi2sd_Vsd_Hpd_Ey = { "vcvtsi2sd", AVX_vcvtsi2sd, Vsd, Hpd, Ey, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtsi2ss_Vss_Hps_Ey = { "vcvtsi2ss", AVX_vcvtsi2ss, Vss, Hps, Ey, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtss2sd_Vsd_Hpd_Wss = { "vcvtss2sd", AVX_vcvtss2sd, Vsd, Hpd, Wss, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvtss2si_Gy_Wss = { "vcvtss2si", AVX_vcvtss2si, Gy, Wss, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvttpd2dq_Vq_Wpd = { "vcvttpd2dq", AVX_vcvttpd2dq, Vq, Wpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvttps2dq_Vdq_Wps = { "vcvttps2dq", AVX_vcvttps2dq, Vdq, Wps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvttsd2si_Gy_Wsd = { "vcvttsd2si", AVX_vcvttsd2si, Gy, Wsd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vcvttss2si_Gy_Wss = { "vcvttss2si", AVX_vcvttss2si, Gy, Wss, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vdivpd_Vpd_Hpd_Wpd = { "vdivpd", AVX_vdivpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vdivps_Vps_Hps_Wps = { "vdivps", AVX_vdivps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vdivsd_Vsd_Hpd_Wsd = { "vdivsd", AVX_vdivsd, Vsd, Hpd, Wsd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vdivss_Vss_Hps_Wss = { "vdivss", AVX_vdivss, Vss, Hps, Wss, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vdppd_Vpd_Hpd_Wpd_Ib = { "vdppd", AVX_vdppd, Vpd, Hpd, Wpd, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vdpps_Vps_Hps_Wps_Ib = { "vdpps", AVX_vdpps, Vps, Hps, Wps, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vextractf128_Wdq_Vdq_Ib = { "vextractf128", AVX_vextractf128, Wdq, Vdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vextracti128_Wdq_Vdq_Ib = { "vextracti128", AVX_vextracti128, Wdq, Vdq, Ib, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vextractps_Ed_Vdq_Ib = { "vextractps", AVX_vextractps, Ed, Vdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd132pd_Vpd_Hpd_Wpd = { "vfmadd132pd", AVX_vfmadd132pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd132ps_Vps_Hps_Wps = { "vfmadd132ps", AVX_vfmadd132ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd132sd_Vpd_Hsd_Wsd = { "vfmadd132sd", AVX_vfmadd132sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd132ss_Vps_Hss_Wss = { "vfmadd132ss", AVX_vfmadd132ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd213pd_Vpd_Hpd_Wpd = { "vfmadd213pd", AVX_vfmadd213pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd213ps_Vps_Hps_Wps = { "vfmadd213ps", AVX_vfmadd213ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd213sd_Vpd_Hsd_Wsd = { "vfmadd213sd", AVX_vfmadd213sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd213ss_Vps_Hss_Wss = { "vfmadd213ss", AVX_vfmadd213ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd231pd_Vpd_Hpd_Wpd = { "vfmadd231pd", AVX_vfmadd231pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd231ps_Vps_Hps_Wps = { "vfmadd231ps", AVX_vfmadd231ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd231sd_Vpd_Hsd_Wsd = { "vfmadd231sd", AVX_vfmadd231sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmadd231ss_Vps_Hss_Wss = { "vfmadd231ss", AVX_vfmadd231ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsub132pd_Vpd_Hpd_Wpd = { "vfmaddsub132pd", AVX_vfmaddsub132pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsub132ps_Vps_Hps_Wps = { "vfmaddsub132ps", AVX_vfmaddsub132ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsub213pd_Vpd_Hpd_Wpd = { "vfmaddsub213pd", AVX_vfmaddsub213pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsub213ps_Vps_Hps_Wps = { "vfmaddsub213ps", AVX_vfmaddsub213ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsub231pd_Vpd_Hpd_Wpd = { "vfmaddsub231pd", AVX_vfmaddsub231pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsub231ps_Vps_Hps_Wps = { "vfmaddsub231ps", AVX_vfmaddsub231ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub132pd_Vpd_Hpd_Wpd = { "vfmsub132pd", AVX_vfmsub132pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub132ps_Vps_Hps_Wps = { "vfmsub132ps", AVX_vfmsub132ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub132sd_Vpd_Hsd_Wsd = { "vfmsub132sd", AVX_vfmsub132sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub132ss_Vps_Hss_Wss = { "vfmsub132ss", AVX_vfmsub132ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub213pd_Vpd_Hpd_Wpd = { "vfmsub213pd", AVX_vfmsub213pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub213ps_Vps_Hps_Wps = { "vfmsub213ps", AVX_vfmsub213ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub213sd_Vpd_Hsd_Wsd = { "vfmsub213sd", AVX_vfmsub213sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub213ss_Vps_Hss_Wss = { "vfmsub213ss", AVX_vfmsub213ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub231pd_Vpd_Hpd_Wpd = { "vfmsub231pd", AVX_vfmsub231pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub231ps_Vps_Hps_Wps = { "vfmsub231ps", AVX_vfmsub231ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub231sd_Vpd_Hsd_Wsd = { "vfmsub231sd", AVX_vfmsub231sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsub231ss_Vps_Hss_Wss = { "vfmsub231ss", AVX_vfmsub231ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubadd132pd_Vpd_Hpd_Wpd = { "vfmsubadd132pd", AVX_vfmsubadd132pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubadd132ps_Vps_Hps_Wps = { "vfmsubadd132ps", AVX_vfmsubadd132ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubadd213pd_Vpd_Hpd_Wpd = { "vfmsubadd213pd", AVX_vfmsubadd213pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubadd213ps_Vps_Hps_Wps = { "vfmsubadd213ps", AVX_vfmsubadd213ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubadd231pd_Vpd_Hpd_Wpd = { "vfmsubadd231pd", AVX_vfmsubadd231pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubadd231ps_Vps_Hps_Wps = { "vfmsubadd231ps", AVX_vfmsubadd231ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd132pd_Vpd_Hpd_Wpd = { "vfnmadd132pd", AVX_vfnmadd132pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd132ps_Vps_Hps_Wps = { "vfnmadd132ps", AVX_vfnmadd132ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd132sd_Vpd_Hsd_Wsd = { "vfnmadd132sd", AVX_vfnmadd132sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd132ss_Vps_Hss_Wss = { "vfnmadd132ss", AVX_vfnmadd132ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd213pd_Vpd_Hpd_Wpd = { "vfnmadd213pd", AVX_vfnmadd213pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd213ps_Vps_Hps_Wps = { "vfnmadd213ps", AVX_vfnmadd213ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd213sd_Vpd_Hsd_Wsd = { "vfnmadd213sd", AVX_vfnmadd213sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd213ss_Vps_Hss_Wss = { "vfnmadd213ss", AVX_vfnmadd213ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd231pd_Vpd_Hpd_Wpd = { "vfnmadd231pd", AVX_vfnmadd231pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd231ps_Vps_Hps_Wps = { "vfnmadd231ps", AVX_vfnmadd231ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd231sd_Vpd_Hsd_Wsd = { "vfnmadd231sd", AVX_vfnmadd231sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmadd231ss_Vps_Hss_Wss = { "vfnmadd231ss", AVX_vfnmadd231ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub132pd_Vpd_Hpd_Wpd = { "vfnmsub132pd", AVX_vfnmsub132pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub132ps_Vps_Hps_Wps = { "vfnmsub132ps", AVX_vfnmsub132ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub132sd_Vpd_Hsd_Wsd = { "vfnmsub132sd", AVX_vfnmsub132sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub132ss_Vps_Hss_Wss = { "vfnmsub132ss", AVX_vfnmsub132ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub213pd_Vpd_Hpd_Wpd = { "vfnmsub213pd", AVX_vfnmsub213pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub213ps_Vps_Hps_Wps = { "vfnmsub213ps", AVX_vfnmsub213ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub213sd_Vpd_Hsd_Wsd = { "vfnmsub213sd", AVX_vfnmsub213sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub213ss_Vps_Hss_Wss = { "vfnmsub213ss", AVX_vfnmsub213ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub231pd_Vpd_Hpd_Wpd = { "vfnmsub231pd", AVX_vfnmsub231pd, Vpd, Hpd, Wpd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub231ps_Vps_Hps_Wps = { "vfnmsub231ps", AVX_vfnmsub231ps, Vps, Hps, Wps, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub231sd_Vpd_Hsd_Wsd = { "vfnmsub231sd", AVX_vfnmsub231sd, Vpd, Hsd, Wsd, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsub231ss_Vps_Hss_Wss = { "vfnmsub231ss", AVX_vfnmsub231ss, Vps, Hss, Wss, XX, IA_AVX_FMA };
const struct BxDisasmOpcodeInfo_t
 Ia_vgatherdd_Vdq_VSib_Hdq = { "vgatherdd", AVX_vgatherdd, Vdq, VSib, Hdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vgatherdpd_Vpd_VSib_Hpd = { "vgatherdpd", AVX_vgatherdpd, Vpd, VSib, Hpd, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vgatherdps_Vps_VSib_Hps = { "vgatherdps", AVX_vgatherdps, Vps, VSib, Hps, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vgatherdq_Vdq_VSib_Hdq = { "vgatherdq", AVX_vgatherdq, Vdq, VSib, Hdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vgatherqd_Vdq_VSib_Hdq = { "vgatherqd", AVX_vgatherqd, Vdq, VSib, Hdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vgatherqpd_Vpd_VSib_Hpd = { "vgatherqpd", AVX_vgatherqpd, Vpd, VSib, Hpd, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vgatherqps_Vps_VSib_Hps = { "vgatherqps", AVX_vgatherqps, Vps, VSib, Hps, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vgatherqq_Vdq_VSib_Hdq = { "vgatherqq", AVX_vgatherqq, Vdq, VSib, Hdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vhaddpd_Vpd_Hpd_Wpd = { "vhaddpd", AVX_vhaddpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vhaddps_Vps_Hps_Wps = { "vhaddps", AVX_vhaddps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vhsubpd_Vpd_Hpd_Wpd = { "vhsubpd", AVX_vhsubpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vhsubps_Vps_Hps_Wps = { "vhsubps", AVX_vhsubps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vinsertf128_Vdq_Hdq_Wdq_Ib = { "vinsertf128", AVX_vinsertf128, Vdq, Hdq, Wdq, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vinserti128_Vdq_Hdq_Wdq_Ib = { "vinserti128", AVX_vinserti128, Vdq, Hdq, Wdq, Ib, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vinsertps_Vps_Hps_Wss_Ib = { "vinsertps", AVX_vinsertps, Vps, Hps, Wss, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vlddqu_Vdq_Mdq = { "vlddqu", AVX_vlddqu, Vdq, Mdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vldmxcsr = { "vldmxcsr", AVX_vldmxcsr, Md, XX, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaskmovd_Mdq_Hdq_Vdq = { "vmaskmovd", AVX_vmaskmovd1, Mdq, Hdq, Vdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaskmovd_Vdq_Hdq_Mdq = { "vmaskmovd", AVX_vmaskmovd2, Vdq, Hdq, Mdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaskmovdqu_Vdq_Udq = { "vmaskmovdqu", AVX_vmaskmovdqu, Vdq, Udq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaskmovpd_Mpd_Hpd_Vpd = { "vmaskmovpd", AVX_vmaskmovpd1, Mpd, Hpd, Vpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaskmovpd_Vpd_Hpd_Mpd = { "vmaskmovpd", AVX_vmaskmovpd2, Vpd, Hpd, Mpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaskmovps_Mps_Hps_Vps = { "vmaskmovps", AVX_vmaskmovps1, Mps, Hps, Vps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaskmovps_Vps_Hps_Mps = { "vmaskmovps", AVX_vmaskmovps2, Vps, Hps, Mps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaskmovq_Mdq_Hdq_Vdq = { "vmaskmovq", AVX_vmaskmovq1, Mdq, Hdq, Vdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaskmovq_Vdq_Hdq_Mdq = { "vmaskmovq", AVX_vmaskmovq2, Vdq, Hdq, Mdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaxpd_Vpd_Hpd_Wpd = { "vmaxpd", AVX_vmaxpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaxps_Vps_Hps_Wps = { "vmaxps", AVX_vmaxps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaxsd_Vsd_Hpd_Wsd = { "vmaxsd", AVX_vmaxsd, Vsd, Hpd, Wsd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmaxss_Vss_Hps_Wss = { "vmaxss", AVX_vmaxss, Vss, Hps, Wss, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vminpd_Vpd_Hpd_Wpd = { "vminpd", AVX_vminpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vminps_Vps_Hps_Wps = { "vminps", AVX_vminps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vminsd_Vsd_Hpd_Wsd = { "vminsd", AVX_vminsd, Vsd, Hpd, Wsd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vminss_Vss_Hps_Wss = { "vminss", AVX_vminss, Vss, Hps, Wss, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovapd_Vpd_Wpd = { "vmovapd", AVX_vmovapd1, Vpd, Wpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovapd_Wpd_Vpd = { "vmovapd", AVX_vmovapd2, Wpd, Vpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovaps_Vps_Wps = { "vmovaps", AVX_vmovaps1, Vps, Wps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovaps_Wps_Vps = { "vmovaps", AVX_vmovaps2, Wps, Vps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovd_Ed_Vd = { "vmovd", AVX_vmovd1, Ed, Vdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovd_Vdq_Ed = { "vmovd", AVX_vmovd2, Vdq, Ed, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovddup_Vdq_Wq = { "vmovddup", AVX_vmovddup, Vdq, Wq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovdqa_Vdq_Wdq = { "vmovdqa", AVX_vmovdqa1, Vdq, Wdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovdqa_Wdq_Vdq = { "vmovdqa", AVX_vmovdqa2, Wdq, Vdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovdqu_Vdq_Wdq = { "vmovdqu", AVX_vmovdqu1, Vdq, Wdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovdqu_Wdq_Vdq = { "vmovdqu", AVX_vmovdqu2, Wdq, Vdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovhlpd_Vpd_Hdq_Udq = { "vmovhlpd", AVX_vmovhlpd, Vpd, Hdq, Udq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovhlps_Vps_Hdq_Udq = { "vmovhlps", AVX_vmovhlps, Vps, Hdq, Udq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovhpd_Mq_Vpd = { "vmovhpd", AVX_vmovhpd1, Mq, Vpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovhpd_Vpd_Hdq_Mq = { "vmovhpd", AVX_vmovhpd2, Vpd, Hdq, Mq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovhps_Mq_Vps = { "vmovhps", AVX_vmovhps1, Mq, Vps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovhps_Vps_Hdq_Mq = { "vmovhps", AVX_vmovhps2, Vps, Hdq, Mq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovlhpd_Vpd_Hdq_Udq = { "vmovlhpd", AVX_vmovlhpd, Vpd, Hdq, Udq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovlhps_Vps_Hdq_Udq = { "vmovlhps", AVX_vmovlhps, Vps, Hdq, Udq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovlpd_Mq_Vpd = { "vmovlpd", AVX_vmovlpd1, Mq, Vpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovlpd_Vpd_Hdq_Mq = { "vmovlpd", AVX_vmovlpd2, Vpd, Hdq, Mq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovlps_Mq_Vps = { "vmovlps", AVX_vmovlps1, Mq, Vps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovlps_Vps_Hdq_Mq = { "vmovlps", AVX_vmovlps2, Vps, Hdq, Mq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovmskpd_Gd_Vpd = { "vmovmskpd", AVX_vmovmskpd, Gd, Vpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovmskps_Gd_Vps = { "vmovmskps", AVX_vmovmskps, Gd, Vps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovntdq_Mdq_Vdq = { "vmovntdq", AVX_vmovntdq, Mdq, Vdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovntdqa_Vdq_Mdq = { "vmovntdqa", AVX_vmovntdqa, Vdq, Mdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovntpd_Mpd_Vpd = { "vmovntpd", AVX_vmovntpd, Mpd, Vpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovntps_Mps_Vps = { "vmovntps", AVX_vmovntps, Mps, Vps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovq_Eq_Vq = { "vmovq", AVX_vmovq1, Eq, Vq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovq_Vdq_Eq = { "vmovq", AVX_vmovq2, Vdq, Eq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovq_Vq_Wq = { "vmovq", AVX_vmovq3, Vq, Wq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovq_Wq_Vq = { "vmovq", AVX_vmovq4, Wq, Vq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovsd_Vsd_Wsd = { "vmovsd", AVX_vmovsd1, Vsd, Hpd, Wsd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovsd_Wsd_Vsd = { "vmovsd", AVX_vmovsd2, Wsd, Vsd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovshdup_Vdq_Wdq = { "vmovshdup", AVX_vmovshdup, Vdq, Wdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovsldup_Vdq_Wdq = { "vmovsldup", AVX_vmovsldup, Vdq, Wdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovss_Vss_Wss = { "vmovss", AVX_vmovss1, Vss, Hps, Wss, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovss_Wss_Vss = { "vmovss", AVX_vmovss2, Wss, Vss, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovupd_Vpd_Wpd = { "vmovupd", AVX_vmovupd1, Vpd, Wpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovupd_Wpd_Vpd = { "vmovupd", AVX_vmovupd2, Wpd, Vpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovups_Vps_Wps = { "vmovups", AVX_vmovups1, Vps, Wps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmovups_Wps_Vps = { "vmovups", AVX_vmovups2, Wps, Vps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmpsadbw_Vdq_Hdq_Wdq_Ib = { "vmpsadbw", AVX_vmpsadbw, Vdq, Hdq, Wdq, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmulpd_Vpd_Hpd_Wpd = { "vmulpd", AVX_vmulpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmulps_Vps_Hps_Wps = { "vmulps", AVX_vmulps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmulsd_Vsd_Hpd_Wsd = { "vmulsd", AVX_vmulsd, Vsd, Hpd, Wsd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vmulss_Vss_Hps_Wss = { "vmulss", AVX_vmulss, Vss, Hps, Wss, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vorpd_Vpd_Hpd_Wpd = { "vorpd", AVX_vorpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vorps_Vps_Hps_Wps = { "vorps", AVX_vorps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpabsb_Vdq_Hdq_Wdq = { "vpabsb", AVX_vpabsb, Vdq, Wdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpabsd_Vdq_Hdq_Wdq = { "vpabsd", AVX_vpabsd, Vdq, Wdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpabsw_Vdq_Hdq_Wdq = { "vpabsw", AVX_vpabsw, Vdq, Wdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpackssdw_Vdq_Hdq_Wdq = { "vpackssdw", AVX_vpackssdw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpacksswb_Vdq_Hdq_Wdq = { "vpacksswb", AVX_vpacksswb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpackusdw_Vdq_Hdq_Wdq = { "vpackusdw", AVX_vpackusdw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpackuswb_Vdq_Hdq_Wdq = { "vpackuswb", AVX_vpackuswb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpaddb_Vdq_Hdq_Wdq = { "vpaddb", AVX_vpaddb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpaddd_Vdq_Hdq_Wdq = { "vpaddd", AVX_vpaddd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpaddq_Vdq_Hdq_Wdq = { "vpaddq", AVX_vpaddq, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpaddsb_Vdq_Hdq_Wdq = { "vpaddsb", AVX_vpaddsb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpaddsw_Vdq_Hdq_Wdq = { "vpaddsw", AVX_vpaddsw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpaddusb_Vdq_Hdq_Wdq = { "vpaddusb", AVX_vpaddusb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpaddusw_Vdq_Hdq_Wdq = { "vpaddusw", AVX_vpaddusw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpaddw_Vdq_Hdq_Wdq = { "vpaddw", AVX_vpaddw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpalignr_Vdq_Hdq_Wdq_Ib = { "vpalignr", AVX_vpalignr, Vdq, Hdq, Wdq, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpand_Vdq_Hdq_Wdq = { "vpand", AVX_vpand, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpandn_Vdq_Hdq_Wdq = { "vpandn", AVX_vpandn, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpavgb_Vdq_Hdq_Wdq = { "vpavgb", AVX_vpavgb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpavgw_Vdq_Hdq_Wdq = { "vpavgw", AVX_vpavgw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpblendd_Vdq_Hdq_Wdq_Ib = { "vpblendd", AVX_vpblendd, Vdq, Hdq, Wdq, Ib, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpblendvb_Vdq_Hdq_Wdq_Ib = { "vpblendvb", AVX_vpblendvb, Vdq, Hdq, Wdq, VIb, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpblendw_Vdq_Hdq_Wdq_Ib = { "vpblendw", AVX_vpblendw, Vdq, Hdq, Wdq, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpbroadcastb_Vdq_Wb = { "vpbroadcastb", AVX_vpbroadcastb, Vdq, Wb, XX, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpbroadcastd_Vdq_Wd = { "vpbroadcastd", AVX_vpbroadcastd, Vdq, Wd, XX, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpbroadcastq_Vdq_Wq = { "vpbroadcastq", AVX_vpbroadcastq, Vdq, Wq, XX, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpbroadcastw_Vdq_Ww = { "vpbroadcastw", AVX_vpbroadcastw, Vdq, Ww, XX, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpclmulqdq_Vdq_Hdq_Wdq_Ib = { "vpclmulqdq", AVX_vpclmulqdq, Vdq, Hdq, Wdq, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpeqb_Vdq_Hdq_Wdq = { "vpcmpeqb", AVX_vpcmpeqb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpeqd_Vdq_Hdq_Wdq = { "vpcmpeqd", AVX_vpcmpeqd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpeqq_Vdq_Hdq_Wdq = { "vpcmpeqq", AVX_vpcmpeqq, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpeqw_Vdq_Hdq_Wdq = { "vpcmpeqw", AVX_vpcmpeqw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpestri_Vdq_Wdq_Ib = { "vpcmpestri", AVX_vpcmpestri, Vdq, Wdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpestrm_Vdq_Wdq_Ib = { "vpcmpestrm", AVX_vpcmpestrm, Vdq, Wdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpgtb_Vdq_Hdq_Wdq = { "vpcmpgtb", AVX_vpcmpgtb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpgtd_Vdq_Hdq_Wdq = { "vpcmpgtd", AVX_vpcmpgtd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpgtq_Vdq_Hdq_Wdq = { "vpcmpgtq", AVX_vpcmpgtq, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpgtw_Vdq_Hdq_Wdq = { "vpcmpgtw", AVX_vpcmpgtw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpistri_Vdq_Wdq_Ib = { "vpcmpistri", AVX_vpcmpistri, Vdq, Wdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmpistrm_Vdq_Wdq_Ib = { "vpcmpistrm", AVX_vpcmpistrm, Vdq, Wdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vperm2f128_Vdq_Hdq_Wdq_Ib = { "vperm2f128", AVX_vperm2f128, Vdq, Hdq, Wdq, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vperm2i128_Vdq_Hdq_Wdq_Ib = { "vperm2128", AVX_vperm2128, Vdq, Hdq, Wdq, Ib, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpermd_Vdq_Hdq_Wdq = { "vpermd", AVX_vpermd, Vdq, Hdq, Wdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpermilpd_Vpd_Hpd_Wpd = { "vpermilpd", AVX_vpermilpd1, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpermilpd_Vpd_Wpd_Ib = { "vpermilpd", AVX_vpermilpd2, Vpd, Wpd, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpermilps_Vps_Hps_Wps = { "vpermilps", AVX_vpermilps1, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpermilps_Vps_Wps_Ib = { "vpermilps", AVX_vpermilps2, Vps, Wps, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpermpd_Vpd_Wpd_Ib = { "vpermpd", AVX_vpermpd, Vpd, Wpd, Ib, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpermps_Vps_Hps_Wps = { "vpermps", AVX_vpermps, Vps, Hps, Wps, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpermq_Vdq_Wdq_Ib = { "vpermq", AVX_vpermq, Vdq, Wdq, Ib, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpextrb_Ebd_Vdq_Ib = { "vpextrb", AVX_vpextrb, Ebd, Vdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpextrd_Ed_Vdq_Ib = { "vpextrd", AVX_vpextrd, Ed, Vdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpextrq_Eq_Vdq_Ib = { "vpextrq", AVX_vpextrq, Eq, Vdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpextrw_Ewd_Vdq_Ib = { "vpextrw", AVX_vpextrw1, Ewd, Vdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpextrw_Gd_Udq_Ib = { "vpextrw", AVX_vpextrw2, Gd, Udq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddd_Vdq_Hdq_Wdq = { "vphaddd", AVX_vphaddd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddsw_Vdq_Hdq_Wdq = { "vphaddsw", AVX_vphaddsw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddw_Vdq_Hdq_Wdq = { "vphaddw", AVX_vphaddw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vphminposuw_Vdq_Wdq = { "vphminposuw", AVX_vphminposuw, Vdq, Wdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vphsubd_Vdq_Hdq_Wdq = { "vphsubd", AVX_vphsubd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vphsubsw_Vdq_Hdq_Wdq = { "vphsubsw", AVX_vphsubsw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vphsubw_Vdq_Hdq_Wdq = { "vphsubw", AVX_vphsubw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpinsrb_Vdq_Hdq_Ed_Ib = { "vpinsrb", AVX_vpinsrb, Vdq, Hdq, Ed, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpinsrd_Vdq_Hdq_Ed_Ib = { "vpinsrd", AVX_vpinsrd, Vdq, Hdq, Ed, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpinsrq_Vdq_Hdq_Eq_Ib = { "vpinsrq", AVX_vpinsrq, Vdq, Hdq, Eq, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpinsrw_Vdq_Hdq_Ew_Ib = { "vpinsrw", AVX_vpinsrw, Vdq, Hdq, Ew, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmaddubsw_Vdq_Hdq_Wdq = { "vpmaddubsw", AVX_vpmaddubsw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmaddwd_Vdq_Hdq_Wdq = { "vpmaddwd", AVX_vpmaddwd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmaxsb_Vdq_Hdq_Wdq = { "vpmaxsb", AVX_vpmaxsb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmaxsd_Vdq_Hdq_Wdq = { "vpmaxsd", AVX_vpmaxsd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmaxsw_Vdq_Hdq_Wdq = { "vpmaxsw", AVX_vpmaxsw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmaxub_Vdq_Hdq_Wdq = { "vpmaxub", AVX_vpmaxub, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmaxud_Vdq_Hdq_Wdq = { "vpmaxud", AVX_vpmaxud, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmaxuw_Vdq_Hdq_Wdq = { "vpmaxuw", AVX_vpmaxuw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpminsb_Vdq_Hdq_Wdq = { "vpminsb", AVX_vpminsb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpminsd_Vdq_Hdq_Wdq = { "vpminsd", AVX_vpminsd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpminsw_Vdq_Hdq_Wdq = { "vpminsw", AVX_vpminsw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpminub_Vdq_Hdq_Wdq = { "vpminub", AVX_vpminub, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpminud_Vdq_Hdq_Wdq = { "vpminud", AVX_vpminud, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpminuw_Vdq_Hdq_Wdq = { "vpminuw", AVX_vpminuw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovmskb_Gd_Udq = { "vpmovmskb", AVX_vpmovmskb, Gd, Udq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovsxbd_Vdq_Wd = { "vpmovsxbd", AVX_vpmovsxbd, Vdq, Wd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovsxbq_Vdq_Ww = { "vpmovsxbq", AVX_vpmovsxbq, Vdq, Ww, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovsxbw_Vdq_Wq = { "vpmovsxbw", AVX_vpmovsxbw, Vdq, Wq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovsxdq_Vdq_Wq = { "vpmovsxdq", AVX_vpmovsxdq, Vdq, Wq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovsxwd_Vdq_Wq = { "vpmovsxwd", AVX_vpmovsxwd, Vdq, Wq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovsxwq_Vdq_Wd = { "vpmovsxwq", AVX_vpmovsxwq, Vdq, Wd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovzxbd_Vdq_Wd = { "vpmovzxbd", AVX_vpmovzxbd, Vdq, Wd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovzxbq_Vdq_Ww = { "vpmovzxbq", AVX_vpmovzxbq, Vdq, Ww, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovzxbw_Vdq_Wq = { "vpmovzxbw", AVX_vpmovzxbw, Vdq, Wq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovzxdq_Vdq_Wq = { "vpmovzxdq", AVX_vpmovzxdq, Vdq, Wq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovzxwd_Vdq_Wq = { "vpmovzxwd", AVX_vpmovzxwd, Vdq, Wq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmovzxwq_Vdq_Wd = { "vpmovzxwq", AVX_vpmovzxwq, Vdq, Wd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmuldq_Vdq_Hdq_Wdq = { "vpmuldq", AVX_vpmuldq, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmulhrsw_Vdq_Hdq_Wdq = { "vpmulhrsw", AVX_vpmulhrsw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmulhuw_Vdq_Hdq_Wdq = { "vpmulhuw", AVX_vpmulhuw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmulhw_Vdq_Hdq_Wdq = { "vpmulhw", AVX_vpmulhw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmulld_Vdq_Hdq_Wdq = { "vpmulld", AVX_vpmulld, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmullw_Vdq_Hdq_Wdq = { "vpmullw", AVX_vpmullw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmuludq_Vdq_Hdq_Wdq = { "vpmuludq", AVX_vpmuludq, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpor_Vdq_Hdq_Wdq = { "vpor", AVX_vpor, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsadbw_Vdq_Hdq_Wdq = { "vpsadbw", AVX_vpsadbw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshufb_Vdq_Hdq_Wdq = { "vpshufb", AVX_vpshufb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshufd_Vdq_Hdq_Wdq_Ib = { "vpshufd", AVX_vpshufd, Vdq, Wdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshufhw_Vdq_Hdq_Wdq_Ib = { "vpshufhw", AVX_vpshufhw, Vdq, Wdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshuflw_Vdq_Hdq_Wdq_Ib = { "vpshuflw", AVX_vpshuflw, Vdq, Wdq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsignb_Vdq_Hdq_Wdq = { "vpsignb", AVX_vpsignb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsignd_Vdq_Hdq_Wdq = { "vpsignd", AVX_vpsignd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsignw_Vdq_Hdq_Wdq = { "vpsignw", AVX_vpsignw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpslld_Hdq_Udq_Ib = { "vpslld", AVX_vpslld1, Hdq, Udq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpslld_Vdq_Hdq_Wdq = { "vpslld", AVX_vpslld2, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpslldq_Hdq_Udq_Ib = { "vpslldq", AVX_vpslldq, Hdq, Udq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsllq_Hdq_Udq_Ib = { "vpsllq", AVX_vpsllq1, Hdq, Udq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsllq_Vdq_Hdq_Wdq = { "vpsllq", AVX_vpsllq2, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsllvd_Vdq_Hdq_Wdq = { "vpsllvd", AVX_vpsllvd, Vdq, Hdq, Wdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsllvq_Vdq_Hdq_Wdq = { "vpsllvq", AVX_vpsllvq, Vdq, Hdq, Wdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsllw_Hdq_Udq_Ib = { "vpsllw", AVX_vpsllw1, Hdq, Udq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsllw_Vdq_Hdq_Wdq = { "vpsllw", AVX_vpsllw2, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsrad_Hdq_Udq_Ib = { "vpsrad", AVX_vpsrad1, Hdq, Udq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsrad_Vdq_Hdq_Wdq = { "vpsrad", AVX_vpsrad2, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsravd_Vdq_Hdq_Wdq = { "vpsravd", AVX_vpsravd, Vdq, Hdq, Wdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsraw_Hdq_Udq_Ib = { "vpsraw", AVX_vpsraw1, Hdq, Udq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsraw_Vdq_Hdq_Wdq = { "vpsraw", AVX_vpsraw2, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsrld_Hdq_Udq_Ib = { "vpsrld", AVX_vpsrld1, Hdq, Udq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsrld_Vdq_Hdq_Wdq = { "vpsrld", AVX_vpsrld2, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsrldq_Hdq_Udq_Ib = { "vpsrldq", AVX_vpsrldq, Hdq, Udq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsrlq_Hdq_Udq_Ib = { "vpsrlq", AVX_vpsrlq1, Hdq, Udq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsrlq_Vdq_Hdq_Wdq = { "vpsrlq", AVX_vpsrlq2, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsrlvd_Vdq_Hdq_Wdq = { "vpsrlvd", AVX_vpsrlvd, Vdq, Hdq, Wdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsrlvq_Vdq_Hdq_Wdq = { "vpsrlvq", AVX_vpsrlvq, Vdq, Hdq, Wdq, XX, IA_AVX2 };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsrlw_Hdq_Udq_Ib = { "vpsrlw", AVX_vpsrlw1, Hdq, Udq, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsrlw_Vdq_Hdq_Wdq = { "vpsrlw", AVX_vpsrlw2, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsubb_Vdq_Hdq_Wdq = { "vpsubb", AVX_vpsubb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsubd_Vdq_Hdq_Wdq = { "vpsubd", AVX_vpsubd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsubq_Vdq_Hdq_Wdq = { "vpsubq", AVX_vpsubq, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsubsb_Vdq_Hdq_Wdq = { "vpsubsb", AVX_vpsubsb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsubsw_Vdq_Hdq_Wdq = { "vpsubsw", AVX_vpsubsw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsubusb_Vdq_Hdq_Wdq = { "vpsubusb", AVX_vpsubusb, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsubusw_Vdq_Hdq_Wdq = { "vpsubusw", AVX_vpsubusw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpsubw_Vdq_Hdq_Wdq = { "vpsubw", AVX_vpsubw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vptest_Vdq_Wdq = { "vptest", AVX_vptest, Vdq, Wdq, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpunpckhbw_Vdq_Hdq_Wdq = { "vpunpckhbw", AVX_vpunpckhbw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpunpckhdq_Vdq_Hdq_Wdq = { "vpunpckhdq", AVX_vpunpckhdq, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpunpckhqdq_Vdq_Hdq_Wdq = { "vpunpckhqdq", AVX_vpunpckhqdq, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpunpckhwd_Vdq_Hdq_Wdq = { "vpunpckhwd", AVX_vpunpckhwd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpunpcklbw_Vdq_Hdq_Wdq = { "vpunpcklbw", AVX_vpunpcklbw, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpunpckldq_Vdq_Hdq_Wdq = { "vpunpckldq", AVX_vpunpckldq, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpunpcklqdq_Vdq_Hdq_Wdq = { "vpunpcklqdq", AVX_vpunpcklqdq, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpunpcklwd_Vdq_Hdq_Wdq = { "vpunpcklwd", AVX_vpunpcklwd, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vpxor_Vdq_Hdq_Wdq = { "vpxor", AVX_vpxor, Vdq, Hdq, Wdq, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vrcpps_Vps_Wps = { "vrcpps", AVX_vrcpps, Vps, Wps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vrcpss_Vss_Hps_Wss = { "vrcpss", AVX_vrcpss, Vss, Hps, Wss, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vroundpd_Vpd_Wpd_Ib = { "vroundpd", AVX_vroundpd, Vpd, Wpd, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vroundps_Vps_Wps_Ib = { "vroundps", AVX_vroundps, Vps, Wps, Ib, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vroundsd_Vsd_Hpd_Wsd_Ib = { "vroundsd", AVX_vroundsd, Vsd, Hpd, Wsd, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vroundss_Vss_Hps_Wss_Ib = { "vroundss", AVX_vroundss, Vss, Hps, Wss, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vrsqrtps_Vps_Wps = { "vrsqrtps", AVX_vrsqrtps, Vps, Wps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vrsqrtss_Vss_Hps_Wss = { "vrsqrtss", AVX_vrsqrtss, Vss, Hps, Wss, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vshufpd_Vpd_Hpd_Wpd_Ib = { "vshufpd", AVX_vshufpd, Vpd, Hpd, Wpd, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vshufps_Vps_Hps_Wps_Ib = { "vshufps", AVX_vshufps, Vps, Hps, Wps, Ib, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vsqrtpd_Vpd_Wpd = { "vsqrtpd", AVX_vsqrtpd, Vpd, Wpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vsqrtps_Vps_Wps = { "vsqrtps", AVX_vsqrtps, Vps, Wps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vsqrtsd_Vsd_Hpd_Wsd = { "vsqrtsd", AVX_vsqrtsd, Vsd, Hpd, Wsd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vsqrtss_Vss_Hps_Wss = { "vsqrtss", AVX_vsqrtss, Vss, Hps, Wss, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vstmxcsr = { "vstmxcsr", AVX_vstmxcsr, Md, XX, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vsubpd_Vpd_Hpd_Wpd = { "vsubpd", AVX_vsubpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vsubps_Vps_Hps_Wps = { "vsubps", AVX_vsubps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vsubsd_Vsd_Hpd_Wsd = { "vsubsd", AVX_vsubsd, Vsd, Hpd, Wsd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vsubss_Vss_Hps_Wss = { "vsubss", AVX_vsubss, Vss, Hps, Wss, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vtestpd_Vpd_Wpd = { "vtestpd", AVX_vtestpd, Vpd, Wpd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vtestps_Vps_Wps = { "vtestps", AVX_vtestps, Vps, Wps, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vucomisd_Vsd_Wsd = { "vucomisd", AVX_vucomisd, Vsd, Wsd, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vucomiss_Vss_Wss = { "vucomiss", AVX_vucomiss, Vss, Wss, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vunpckhpd_Vpd_Hpd_Wpd = { "vunpckhpd", AVX_vunpckhpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vunpckhps_Vps_Hps_Wps = { "vunpckhps", AVX_vunpckhps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vunpcklpd_Vpd_Hpd_Wpd = { "vunpcklpd", AVX_vunpcklpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vunpcklps_Vps_Hps_Wps = { "vunpcklps", AVX_vunpcklps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vxorpd_Vpd_Hpd_Wpd = { "vxorpd", AVX_vxorpd, Vpd, Hpd, Wpd, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vxorps_Vps_Hps_Wps = { "vxorps", AVX_vxorps, Vps, Hps, Wps, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vzerall = { "vzeroall", AVX_vzeroall, XX, XX, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_vzeroupper = { "vzeroupper", AVX_vzeroupper, XX, XX, XX, XX, IA_AVX };
const struct BxDisasmOpcodeInfo_t
 Ia_frczpd_Vpd_Wpd = { "frczpd", AVX_frczpd, Vpd, Wpd, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_frczps_Vps_Wps = { "frczps", AVX_frczps, Vps, Wps, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_frczsd_Vsd_Wsd = { "frczsd", AVX_frczsd, Vsd, Wsd, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_frczss_Vss_Wss = { "frczss", AVX_frczss, Vss, Wss, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmov_Vdq_Hdq_VIb_Wdq = { "vpcmov", AVX_vpcmov1, Vdq, Hdq, VIb, Wdq, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcmov_Vdq_Hdq_Wdq_VIb = { "vpcmov", AVX_vpcmov2, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcomb_Vdq_Hdq_Wdq_Ib = { "vpcomb", AVX_vpcomb, Vdq, Hdq, Wdq, Ib, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcomd_Vdq_Hdq_Wdq_Ib = { "vpcomd", AVX_vpcomd, Vdq, Hdq, Wdq, Ib, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcomq_Vdq_Hdq_Wdq_Ib = { "vpcomq", AVX_vpcomq, Vdq, Hdq, Wdq, Ib, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcomub_Vdq_Hdq_Wdq_Ib = { "vpcomub", AVX_vpcomub, Vdq, Hdq, Wdq, Ib, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcomud_Vdq_Hdq_Wdq_Ib = { "vpcomud", AVX_vpcomud, Vdq, Hdq, Wdq, Ib, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcomuq_Vdq_Hdq_Wdq_Ib = { "vpcomuq", AVX_vpcomuq, Vdq, Hdq, Wdq, Ib, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcomuw_Vdq_Hdq_Wdq_Ib = { "vpcomuw", AVX_vpcomuw, Vdq, Hdq, Wdq, Ib, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpcomw_Vdq_Hdq_Wdq_Ib = { "vpcomw", AVX_vpcomw, Vdq, Hdq, Wdq, Ib, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddbd_Vdq_Wdq = { "vphaddbd", AVX_vphaddbd, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddbq_Vdq_Wdq = { "vphaddbq", AVX_vphaddbq, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddbw_Vdq_Wdq = { "vphaddbw", AVX_vphaddbw, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphadddq_Vdq_Wdq = { "vphadddq", AVX_vphadddq, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddubd_Vdq_Wdq = { "vphaddubd", AVX_vphaddubd, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddubq_Vdq_Wdq = { "vphaddubq", AVX_vphaddubq, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddubw_Vdq_Wdq = { "vphaddubw", AVX_vphaddubw, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddudq_Vdq_Wdq = { "vphaddudq", AVX_vphaddudq, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphadduwd_Vdq_Wdq = { "vphadduwd", AVX_vphadduwd, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphadduwq_Vdq_Wdq = { "vphadduwq", AVX_vphadduwq, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddwd_Vdq_Wdq = { "vphaddwd", AVX_vphaddwd, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphaddwq_Vdq_Wdq = { "vphaddwq", AVX_vphaddwq, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphsubbw_Vdq_Wdq = { "vphsubbw", AVX_vphsubbw, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphsubdq_Vdq_Wdq = { "vphsubdq", AVX_vphsubdq, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vphsubwd_Vdq_Wdq = { "vphsubwd", AVX_vphsubwd, Vdq, Wdq, XX, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmacsdd_Vdq_Hdq_Wdq_VIb = { "vpmacsdd", AVX_vpmacsdd, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmacsdqh_Vdq_Hdq_Wdq_VIb = { "vpmacsdqh", AVX_vpmacsdqh, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmacsdql_Vdq_Hdq_Wdq_VIb = { "vpmacsdql", AVX_vpmacsdql, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmacssdd_Vdq_Hdq_Wdq_VIb = { "vpmacssdd", AVX_vpmacssdd, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmacssdqh_Vdq_Hdq_Wdq_VIb = { "vpmacssdqh", AVX_vpmacssdqh, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmacssdql_Vdq_Hdq_Wdq_VIb = { "vpmacssdql", AVX_vpmacssdql, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmacsswd_Vdq_Hdq_Wdq_VIb = { "vpmacsswd", AVX_vpmacsswd, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmacssww_Vdq_Hdq_Wdq_VIb = { "vpmacssww", AVX_vpmacssww, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmacswd_Vdq_Hdq_Wdq_VIb = { "vpmacswd", AVX_vpmacswd, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmacsww_Vdq_Hdq_Wdq_VIb = { "vpmacsww", AVX_vpmacsww, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmadcsswd_Vdq_Hdq_Wdq_VIb = { "vpmadcsswd", AVX_vpmadcsswd, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpmadcswd_Vdq_Hdq_Wdq_VIb = { "vpmadcswd", AVX_vpmadcswd, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpperm_Vdq_Hdq_VIb_Wdq = { "vpperm", AVX_vpperm1, Vdq, Hdq, VIb, Wdq, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpperm_Vdq_Hdq_Wdq_VIb = { "vpperm", AVX_vpperm2, Vdq, Hdq, Wdq, VIb, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotb_Vdq_Hdq_Wdq = { "vprotb", AVX_vprotb1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotb_Vdq_Wdq_Hdq = { "vprotb", AVX_vprotb2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotb_Vdq_Wdq_Ib = { "vprotb", AVX_vprotb3, Vdq, Wdq, Ib, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotd_Vdq_Hdq_Wdq = { "vprotd", AVX_vprotd1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotd_Vdq_Wdq_Hdq = { "vprotd", AVX_vprotd2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotd_Vdq_Wdq_Ib = { "vprotd", AVX_vprotd3, Vdq, Wdq, Ib, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotq_Vdq_Hdq_Wdq = { "vprotq", AVX_vprotq1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotq_Vdq_Wdq_Hdq = { "vprotq", AVX_vprotq2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotq_Vdq_Wdq_Ib = { "vprotq", AVX_vprotq3, Vdq, Wdq, Ib, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotw_Vdq_Hdq_Wdq = { "vprotw", AVX_vprotw1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotw_Vdq_Wdq_Hdq = { "vprotw", AVX_vprotw2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vprotw_Vdq_Wdq_Ib = { "vprotw", AVX_vprotw3, Vdq, Wdq, Ib, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshab_Vdq_Hdq_Wdq = { "vpshab", AVX_vpshab1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshab_Vdq_Wdq_Hdq = { "vpshab", AVX_vpshab2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshad_Vdq_Hdq_Wdq = { "vpshad", AVX_vpshad1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshad_Vdq_Wdq_Hdq = { "vpshad", AVX_vpshad2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshaq_Vdq_Hdq_Wdq = { "vpshaq", AVX_vpshaq1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshaq_Vdq_Wdq_Hdq = { "vpshaq", AVX_vpshaq2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshaw_Vdq_Hdq_Wdq = { "vpshaw", AVX_vpshaw1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshaw_Vdq_Wdq_Hdq = { "vpshaw", AVX_vpshaw2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshlb_Vdq_Hdq_Wdq = { "vpshlb", AVX_vpshlb1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshlb_Vdq_Wdq_Hdq = { "vpshlb", AVX_vpshlb2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshld_Vdq_Hdq_Wdq = { "vpshld", AVX_vpshld1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshld_Vdq_Wdq_Hdq = { "vpshld", AVX_vpshld2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshlq_Vdq_Hdq_Wdq = { "vpshlq", AVX_vpshlq1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshlq_Vdq_Wdq_Hdq = { "vpshlq", AVX_vpshlq2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshlw_Vdq_Hdq_Wdq = { "vpshlw", AVX_vpshlw1, Vdq, Hdq, Wdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_vpshlw_Vdq_Wdq_Hdq = { "vpshlw", AVX_vpshlw2, Vdq, Wdq, Hdq, XX, IA_XOP };
const struct BxDisasmOpcodeInfo_t
 Ia_andn_Gy_By_Ey = { "andn", AVX_andn, Gy, By, Ey, XX, IA_BMI1 };
const struct BxDisasmOpcodeInfo_t
 Ia_bextr_Gy_Ey_By = { "bextr", AVX_bextr1, Gy, Ey, By, XX, IA_BMI1 };
const struct BxDisasmOpcodeInfo_t
 Ia_blsi_By_Ey = { "blsi", AVX_blsi, By, Gy, XX, XX, IA_BMI1 };
const struct BxDisasmOpcodeInfo_t
 Ia_blsmsk_By_Ey = { "blsmsk", AVX_blsmsk, By, Gy, XX, XX, IA_BMI1 };
const struct BxDisasmOpcodeInfo_t
 Ia_blsr_By_Ey = { "blsr", AVX_blsr, By, Gy, XX, XX, IA_BMI1 };
const struct BxDisasmOpcodeInfo_t
 Ia_bzhi_Gy_Ey_By = { "bzhi", AVX_bzhi, Gy, Ey, By, XX, IA_BMI2 };
const struct BxDisasmOpcodeInfo_t
 Ia_mulx_By_Gy_Ey = { "mulx", AVX_mulx, By, Gy, Ey, XX, IA_BMI2 };
const struct BxDisasmOpcodeInfo_t
 Ia_pdep_Gy_By_Ey = { "pdep", AVX_pdep, Gy, By, Ey, XX, IA_BMI2 };
const struct BxDisasmOpcodeInfo_t
 Ia_pext_Gy_By_Ey = { "pext", AVX_pext, Gy, By, Ey, XX, IA_BMI2 };
const struct BxDisasmOpcodeInfo_t
 Ia_rorx_Gy_Ey_Ib = { "rorx", AVX_rorx, Gy, Ey, Ib, XX, IA_BMI2 };
const struct BxDisasmOpcodeInfo_t
 Ia_sarx_Gy_Ey_By = { "sarx", AVX_sarx, Gy, Ey, By, XX, IA_BMI2 };
const struct BxDisasmOpcodeInfo_t
 Ia_shlx_Gy_Ey_By = { "shlx", AVX_shlx, Gy, Ey, By, XX, IA_BMI2 };
const struct BxDisasmOpcodeInfo_t
 Ia_shrx_Gy_Ey_By = { "shrx", AVX_shrx, Gy, Ey, By, XX, IA_BMI2 };
const struct BxDisasmOpcodeInfo_t
 Ia_tzcntl_Gd_Ed = { "tzcntl", AVX_tzcntl, Gd, Ed, XX, XX, IA_BMI1 };
const struct BxDisasmOpcodeInfo_t
 Ia_tzcntq_Gq_Eq = { "tzcntq", AVX_tzcntq, Gq, Eq, XX, XX, IA_BMI1 };
const struct BxDisasmOpcodeInfo_t
 Ia_tzcntw_Gw_Ew = { "tzcntw", AVX_tzcntw, Gw, Ew, XX, XX, IA_BMI1 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddpd_Vpd_Hpd_VIb_Wpd = { "vfmaddpd", AVX_vfmaddpd1, Vpd, Hpd, VIb, Wpd, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddpd_Vpd_Hpd_Wpd_VIb = { "vfmaddpd", AVX_vfmaddpd2, Vpd, Hpd, Wpd, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddps_Vps_Hps_VIb_Wps = { "vfmaddps", AVX_vfmaddps1, Vps, Hps, VIb, Wps, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddps_Vps_Hps_Wps_VIb = { "vfmaddps", AVX_vfmaddps2, Vps, Hps, Wps, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsd_Vsd_Hsd_VIb_Wsd = { "vfmaddsd", AVX_vfmaddsd1, Vsd, Hsd, VIb, Wsd, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsd_Vsd_Hsd_Wsd_VIb = { "vfmaddsd", AVX_vfmaddsd2, Vsd, Hsd, Wsd, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddss_Vss_Hss_VIb_Wss = { "vfmaddss", AVX_vfmaddss1, Vss, Hss, VIb, Wss, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddss_Vss_Hss_Wss_VIb = { "vfmaddss", AVX_vfmaddss2, Vss, Hss, Wss, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsubpd_Vpd_Hpd_VIb_Wpd = { "vfmaddsubpd", AVX_vfmaddsubpd1, Vpd, Hpd, VIb, Wpd, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsubpd_Vpd_Hpd_Wpd_VIb = { "vfmaddsubpd", AVX_vfmaddsubpd2, Vpd, Hpd, Wpd, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsubps_Vps_Hps_VIb_Wps = { "vfmaddsubps", AVX_vfmaddsubps1, Vps, Hps, VIb, Wps, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmaddsubps_Vps_Hps_Wps_VIb = { "vfmaddsubps", AVX_vfmaddsubps2, Vps, Hps, Wps, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubaddpd_Vpd_Hpd_VIb_Wpd = { "vfmsubaddpd", AVX_vfmsubaddpd1, Vpd, Hpd, VIb, Wpd, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubaddpd_Vpd_Hpd_Wpd_VIb = { "vfmsubaddpd", AVX_vfmsubaddpd2, Vpd, Hpd, Wpd, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubaddps_Vps_Hps_VIb_Wps = { "vfmsubaddps", AVX_vfmsubaddps1, Vps, Hps, VIb, Wps, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubaddps_Vps_Hps_Wps_VIb = { "vfmsubaddps", AVX_vfmsubaddps2, Vps, Hps, Wps, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubpd_Vpd_Hpd_VIb_Wpd = { "vfmsubpd", AVX_vfmsubpd1, Vpd, Hpd, VIb, Wpd, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubpd_Vpd_Hpd_Wpd_VIb = { "vfmsubpd", AVX_vfmsubpd2, Vpd, Hpd, Wpd, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubps_Vps_Hps_VIb_Wps = { "vfmsubps", AVX_vfmsubps1, Vps, Hps, VIb, Wps, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubps_Vps_Hps_Wps_VIb = { "vfmsubps", AVX_vfmsubps2, Vps, Hps, Wps, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubsd_Vsd_Hsd_VIb_Wsd = { "vfmsubsd", AVX_vfmsubsd1, Vsd, Hsd, VIb, Wsd, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubsd_Vsd_Hsd_Wsd_VIb = { "vfmsubsd", AVX_vfmsubsd2, Vsd, Hsd, Wsd, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubss_Vss_Hss_VIb_Wss = { "vfmsubss", AVX_vfmsubss1, Vss, Hss, VIb, Wss, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfmsubss_Vss_Hss_Wss_VIb = { "vfmsubss", AVX_vfmsubss2, Vss, Hss, Wss, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmaddpd_Vpd_Hpd_VIb_Wpd = { "vfnmaddpd", AVX_vfnmaddpd1, Vpd, Hpd, VIb, Wpd, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmaddpd_Vpd_Hpd_Wpd_VIb = { "vfnmaddpd", AVX_vfnmaddpd2, Vpd, Hpd, Wpd, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmaddps_Vps_Hps_VIb_Wps = { "vfnmaddps", AVX_vfnmaddps1, Vps, Hps, VIb, Wps, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmaddps_Vps_Hps_Wps_VIb = { "vfnmaddps", AVX_vfnmaddps2, Vps, Hps, Wps, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmaddsd_Vsd_Hsd_VIb_Wsd = { "vfnmaddsd", AVX_vfnmaddsd1, Vsd, Hsd, VIb, Wsd, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmaddsd_Vsd_Hsd_Wsd_VIb = { "vfnmaddsd", AVX_vfnmaddsd2, Vsd, Hsd, Wsd, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmaddss_Vss_Hss_VIb_Wss = { "vfnmaddss", AVX_vfnmaddss1, Vss, Hss, VIb, Wss, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmaddss_Vss_Hss_Wss_VIb = { "vfnmaddss", AVX_vfnmaddss2, Vss, Hss, Wss, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsubpd_Vpd_Hpd_VIb_Wpd = { "vfnmsubpd", AVX_vfnmsubpd1, Vpd, Hpd, VIb, Wpd, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsubpd_Vpd_Hpd_Wpd_VIb = { "vfnmsubpd", AVX_vfnmsubpd2, Vpd, Hpd, Wpd, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsubps_Vps_Hps_VIb_Wps = { "vfnmsubps", AVX_vfnmsubps1, Vps, Hps, VIb, Wps, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsubps_Vps_Hps_Wps_VIb = { "vfnmsubps", AVX_vfnmsubps2, Vps, Hps, Wps, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsubsd_Vsd_Hsd_VIb_Wsd = { "vfnmsubsd", AVX_vfnmsubsd1, Vsd, Hsd, VIb, Wsd, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsubsd_Vsd_Hsd_Wsd_VIb = { "vfnmsubsd", AVX_vfnmsubsd2, Vsd, Hsd, Wsd, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsubss_Vss_Hss_VIb_Wss = { "vfnmsubss", AVX_vfnmsubss1, Vss, Hss, VIb, Wss, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_vfnmsubss_Vss_Hss_Wss_VIb = { "vfnmsubss", AVX_vfnmsubss2, Vss, Hss, Wss, VIb, IA_FMA4 };
const struct BxDisasmOpcodeInfo_t
 Ia_bextr_Gy_Ey_Id = { "bextr", AVX_bextr2, Gy, Ey, Id, XX, IA_TBM };
const struct BxDisasmOpcodeInfo_t
 Ia_blcfill_By_Ey = { "blcfill", AVX_blcfill, Gy, By, Ey, XX, IA_TBM };
const struct BxDisasmOpcodeInfo_t
 Ia_blci_By_Ey = { "blci", AVX_blci, Gy, By, Ey, XX, IA_TBM };
const struct BxDisasmOpcodeInfo_t
 Ia_blcic_By_Ey = { "blcic", AVX_blcic, Gy, By, Ey, XX, IA_TBM };
const struct BxDisasmOpcodeInfo_t
 Ia_blcmsk_By_Ey = { "blcmsk", AVX_blcmsk, Gy, By, Ey, XX, IA_TBM };
const struct BxDisasmOpcodeInfo_t
 Ia_blcs_By_Ey = { "blcs", AVX_blcs, Gy, By, Ey, XX, IA_TBM };
const struct BxDisasmOpcodeInfo_t
 Ia_blsfill_By_Ey = { "blsfill", AVX_blsfill, Gy, By, Ey, XX, IA_TBM };
const struct BxDisasmOpcodeInfo_t
 Ia_blsic_By_Ey = { "blsic", AVX_blsic, Gy, By, Ey, XX, IA_TBM };
const struct BxDisasmOpcodeInfo_t
 Ia_t1mskc_By_Ey = { "t1mskc", AVX_t1mskc, Gy, By, Ey, XX, IA_TBM };
const struct BxDisasmOpcodeInfo_t
 Ia_tzmsk_By_Ey = { "tzmsk", AVX_tzmsk, Gy, By, Ey, XX, IA_TBM };


const struct BxDisasmOpcodeInfo_t *opcode_map[] = {
/* AVX_vaddpd */ &Ia_vaddpd_Vpd_Hpd_Wpd,
/* AVX_vaddps */ &Ia_vaddps_Vps_Hps_Wps,
/* AVX_vaddsd */ &Ia_vaddsd_Vsd_Hpd_Wsd,
/* AVX_vaddss */ &Ia_vaddss_Vss_Hps_Wss,
/* AVX_vaddsubpd */ &Ia_vaddsubpd_Vpd_Hpd_Wpd,
/* AVX_vaddsubps */ &Ia_vaddsubps_Vps_Hps_Wps,
/* AVX_vaesdec */ &Ia_vaesdec_Vdq_Hdq_Wdq,
/* AVX_vaesdeclast */ &Ia_vaesdeclast_Vdq_Hdq_Wdq,
/* AVX_vaesenc */ &Ia_vaesenc_Vdq_Hdq_Wdq,
/* AVX_vaesenclast */ &Ia_vaesenclast_Vdq_Hdq_Wdq,
/* AVX_vaesimc */ &Ia_vaesimc_Vdq_Wdq,
/* AVX_vaeskeygenassist */ &Ia_vaeskeygenassist_Vdq_Wdq_Ib,
/* AVX_vandnpd */ &Ia_vandnpd_Vpd_Hpd_Wpd,
/* AVX_vandnps */ &Ia_vandnps_Vps_Hps_Wps,
/* AVX_vandpd */ &Ia_vandpd_Vpd_Hpd_Wpd,
/* AVX_vandps */ &Ia_vandps_Vps_Hps_Wps,
/* AVX_vblendpd */ &Ia_vblendpd_Vpd_Hpd_Wpd_Ib,
/* AVX_vblendps */ &Ia_vblendps_Vps_Hps_Wps_Ib,
/* AVX_vblendvpd */ &Ia_vblendvpd_Vpd_Hpd_Wpd_Ib,
/* AVX_vblendvps */ &Ia_vblendvps_Vps_Hps_Wps_Ib,
/* AVX_vbroadcastf128 */ &Ia_vbroadcastf128_Vdq_Mdq,
/* AVX_vbroadcasti128 */ &Ia_vbroadcasti128_Vdq_Mdq,
/* AVX_vbroadcastsd */ &Ia_vbroadcastsd_Vpd_Wsd,
/* AVX_vbroadcastss */ &Ia_vbroadcastss_Vps_Wss,
/* AVX_vcmppd */ &Ia_vcmppd_Vpd_Hpd_Wpd_Ib,
/* AVX_vcmpps */ &Ia_vcmpps_Vps_Hps_Wps_Ib,
/* AVX_vcmpsd */ &Ia_vcmpsd_Vsd_Hpd_Wsd_Ib,
/* AVX_vcmpss */ &Ia_vcmpss_Vss_Hps_Wss_Ib,
/* AVX_vcomisd */ &Ia_vcomisd_Vsd_Wsd,
/* AVX_vcomiss */ &Ia_vcomiss_Vss_Wss,
/* AVX_vcvtdq2pd */ &Ia_vcvtdq2pd_Vpd_Wq,
/* AVX_vcvtdq2ps */ &Ia_vcvtdq2ps_Vps_Wdq,
/* AVX_vcvtpd2dq */ &Ia_vcvtpd2dq_Vq_Wpd,
/* AVX_vcvtpd2ps */ &Ia_vcvtpd2ps_Vps_Wpd,
/* AVX_vcvtph2ps */ &Ia_vcvtph2ps_Vps_Wq,
/* AVX_vcvtps2dq */ &Ia_vcvtps2dq_Vdq_Wps,
/* AVX_vcvtps2pd */ &Ia_vcvtps2pd_Vpd_Wps,
/* AVX_vcvtps2ph */ &Ia_vcvtps2ph_Wq_Vps_Ib,
/* AVX_vcvtsd2si */ &Ia_vcvtsd2si_Gy_Wsd,
/* AVX_vcvtsd2ss */ &Ia_vcvtsd2ss_Vss_Hps_Wsd,
/* AVX_vcvtsi2sd */ &Ia_vcvtsi2sd_Vsd_Hpd_Ey,
/* AVX_vcvtsi2ss */ &Ia_vcvtsi2ss_Vss_Hps_Ey,
/* AVX_vcvtss2sd */ &Ia_vcvtss2sd_Vsd_Hpd_Wss,
/* AVX_vcvtss2si */ &Ia_vcvtss2si_Gy_Wss,
/* AVX_vcvttpd2dq */ &Ia_vcvttpd2dq_Vq_Wpd,
/* AVX_vcvttps2dq */ &Ia_vcvttps2dq_Vdq_Wps,
/* AVX_vcvttsd2si */ &Ia_vcvttsd2si_Gy_Wsd,
/* AVX_vcvttss2si */ &Ia_vcvttss2si_Gy_Wss,
/* AVX_vdivpd */ &Ia_vdivpd_Vpd_Hpd_Wpd,
/* AVX_vdivps */ &Ia_vdivps_Vps_Hps_Wps,
/* AVX_vdivsd */ &Ia_vdivsd_Vsd_Hpd_Wsd,
/* AVX_vdivss */ &Ia_vdivss_Vss_Hps_Wss,
/* AVX_vdppd */ &Ia_vdppd_Vpd_Hpd_Wpd_Ib,
/* AVX_vdpps */ &Ia_vdpps_Vps_Hps_Wps_Ib,
/* AVX_vextractf128 */ &Ia_vextractf128_Wdq_Vdq_Ib,
/* AVX_vextracti128 */ &Ia_vextracti128_Wdq_Vdq_Ib,
/* AVX_vextractps */ &Ia_vextractps_Ed_Vdq_Ib,
/* AVX_vfmadd132pd */ &Ia_vfmadd132pd_Vpd_Hpd_Wpd,
/* AVX_vfmadd132ps */ &Ia_vfmadd132ps_Vps_Hps_Wps,
/* AVX_vfmadd132sd */ &Ia_vfmadd132sd_Vpd_Hsd_Wsd,
/* AVX_vfmadd132ss */ &Ia_vfmadd132ss_Vps_Hss_Wss,
/* AVX_vfmadd213pd */ &Ia_vfmadd213pd_Vpd_Hpd_Wpd,
/* AVX_vfmadd213ps */ &Ia_vfmadd213ps_Vps_Hps_Wps,
/* AVX_vfmadd213sd */ &Ia_vfmadd213sd_Vpd_Hsd_Wsd,
/* AVX_vfmadd213ss */ &Ia_vfmadd213ss_Vps_Hss_Wss,
/* AVX_vfmadd231pd */ &Ia_vfmadd231pd_Vpd_Hpd_Wpd,
/* AVX_vfmadd231ps */ &Ia_vfmadd231ps_Vps_Hps_Wps,
/* AVX_vfmadd231sd */ &Ia_vfmadd231sd_Vpd_Hsd_Wsd,
/* AVX_vfmadd231ss */ &Ia_vfmadd231ss_Vps_Hss_Wss,
/* AVX_vfmaddsub132pd */ &Ia_vfmaddsub132pd_Vpd_Hpd_Wpd,
/* AVX_vfmaddsub132ps */ &Ia_vfmaddsub132ps_Vps_Hps_Wps,
/* AVX_vfmaddsub213pd */ &Ia_vfmaddsub213pd_Vpd_Hpd_Wpd,
/* AVX_vfmaddsub213ps */ &Ia_vfmaddsub213ps_Vps_Hps_Wps,
/* AVX_vfmaddsub231pd */ &Ia_vfmaddsub231pd_Vpd_Hpd_Wpd,
/* AVX_vfmaddsub231ps */ &Ia_vfmaddsub231ps_Vps_Hps_Wps,
/* AVX_vfmsub132pd */ &Ia_vfmsub132pd_Vpd_Hpd_Wpd,
/* AVX_vfmsub132ps */ &Ia_vfmsub132ps_Vps_Hps_Wps,
/* AVX_vfmsub132sd */ &Ia_vfmsub132sd_Vpd_Hsd_Wsd,
/* AVX_vfmsub132ss */ &Ia_vfmsub132ss_Vps_Hss_Wss,
/* AVX_vfmsub213pd */ &Ia_vfmsub213pd_Vpd_Hpd_Wpd,
/* AVX_vfmsub213ps */ &Ia_vfmsub213ps_Vps_Hps_Wps,
/* AVX_vfmsub213sd */ &Ia_vfmsub213sd_Vpd_Hsd_Wsd,
/* AVX_vfmsub213ss */ &Ia_vfmsub213ss_Vps_Hss_Wss,
/* AVX_vfmsub231pd */ &Ia_vfmsub231pd_Vpd_Hpd_Wpd,
/* AVX_vfmsub231ps */ &Ia_vfmsub231ps_Vps_Hps_Wps,
/* AVX_vfmsub231sd */ &Ia_vfmsub231sd_Vpd_Hsd_Wsd,
/* AVX_vfmsub231ss */ &Ia_vfmsub231ss_Vps_Hss_Wss,
/* AVX_vfmsubadd132pd */ &Ia_vfmsubadd132pd_Vpd_Hpd_Wpd,
/* AVX_vfmsubadd132ps */ &Ia_vfmsubadd132ps_Vps_Hps_Wps,
/* AVX_vfmsubadd213pd */ &Ia_vfmsubadd213pd_Vpd_Hpd_Wpd,
/* AVX_vfmsubadd213ps */ &Ia_vfmsubadd213ps_Vps_Hps_Wps,
/* AVX_vfmsubadd231pd */ &Ia_vfmsubadd231pd_Vpd_Hpd_Wpd,
/* AVX_vfmsubadd231ps */ &Ia_vfmsubadd231ps_Vps_Hps_Wps,
/* AVX_vfnmadd132pd */ &Ia_vfnmadd132pd_Vpd_Hpd_Wpd,
/* AVX_vfnmadd132ps */ &Ia_vfnmadd132ps_Vps_Hps_Wps,
/* AVX_vfnmadd132sd */ &Ia_vfnmadd132sd_Vpd_Hsd_Wsd,
/* AVX_vfnmadd132ss */ &Ia_vfnmadd132ss_Vps_Hss_Wss,
/* AVX_vfnmadd213pd */ &Ia_vfnmadd213pd_Vpd_Hpd_Wpd,
/* AVX_vfnmadd213ps */ &Ia_vfnmadd213ps_Vps_Hps_Wps,
/* AVX_vfnmadd213sd */ &Ia_vfnmadd213sd_Vpd_Hsd_Wsd,
/* AVX_vfnmadd213ss */ &Ia_vfnmadd213ss_Vps_Hss_Wss,
/* AVX_vfnmadd231pd */ &Ia_vfnmadd231pd_Vpd_Hpd_Wpd,
/* AVX_vfnmadd231ps */ &Ia_vfnmadd231ps_Vps_Hps_Wps,
/* AVX_vfnmadd231sd */ &Ia_vfnmadd231sd_Vpd_Hsd_Wsd,
/* AVX_vfnmadd231ss */ &Ia_vfnmadd231ss_Vps_Hss_Wss,
/* AVX_vfnmsub132pd */ &Ia_vfnmsub132pd_Vpd_Hpd_Wpd,
/* AVX_vfnmsub132ps */ &Ia_vfnmsub132ps_Vps_Hps_Wps,
/* AVX_vfnmsub132sd */ &Ia_vfnmsub132sd_Vpd_Hsd_Wsd,
/* AVX_vfnmsub132ss */ &Ia_vfnmsub132ss_Vps_Hss_Wss,
/* AVX_vfnmsub213pd */ &Ia_vfnmsub213pd_Vpd_Hpd_Wpd,
/* AVX_vfnmsub213ps */ &Ia_vfnmsub213ps_Vps_Hps_Wps,
/* AVX_vfnmsub213sd */ &Ia_vfnmsub213sd_Vpd_Hsd_Wsd,
/* AVX_vfnmsub213ss */ &Ia_vfnmsub213ss_Vps_Hss_Wss,
/* AVX_vfnmsub231pd */ &Ia_vfnmsub231pd_Vpd_Hpd_Wpd,
/* AVX_vfnmsub231ps */ &Ia_vfnmsub231ps_Vps_Hps_Wps,
/* AVX_vfnmsub231sd */ &Ia_vfnmsub231sd_Vpd_Hsd_Wsd,
/* AVX_vfnmsub231ss */ &Ia_vfnmsub231ss_Vps_Hss_Wss,
/* AVX_vgatherdd */ &Ia_vgatherdd_Vdq_VSib_Hdq,
/* AVX_vgatherdpd */ &Ia_vgatherdpd_Vpd_VSib_Hpd,
/* AVX_vgatherdps */ &Ia_vgatherdps_Vps_VSib_Hps,
/* AVX_vgatherdq */ &Ia_vgatherdq_Vdq_VSib_Hdq,
/* AVX_vgatherqd */ &Ia_vgatherqd_Vdq_VSib_Hdq,
/* AVX_vgatherqpd */ &Ia_vgatherqpd_Vpd_VSib_Hpd,
/* AVX_vgatherqps */ &Ia_vgatherqps_Vps_VSib_Hps,
/* AVX_vgatherqq */ &Ia_vgatherqq_Vdq_VSib_Hdq,
/* AVX_vhaddpd */ &Ia_vhaddpd_Vpd_Hpd_Wpd,
/* AVX_vhaddps */ &Ia_vhaddps_Vps_Hps_Wps,
/* AVX_vhsubpd */ &Ia_vhsubpd_Vpd_Hpd_Wpd,
/* AVX_vhsubps */ &Ia_vhsubps_Vps_Hps_Wps,
/* AVX_vinsertf128 */ &Ia_vinsertf128_Vdq_Hdq_Wdq_Ib,
/* AVX_vinserti128 */ &Ia_vinserti128_Vdq_Hdq_Wdq_Ib,
/* AVX_vinsertps */ &Ia_vinsertps_Vps_Hps_Wss_Ib,
/* AVX_vlddqu */ &Ia_vlddqu_Vdq_Mdq,
/* AVX_vldmxcsr */ &Ia_vldmxcsr,
/* AVX_vmaskmovd1 */ &Ia_vmaskmovd_Mdq_Hdq_Vdq,
/* AVX_vmaskmovd2 */ &Ia_vmaskmovd_Vdq_Hdq_Mdq,
/* AVX_vmaskmovdqu */ &Ia_vmaskmovdqu_Vdq_Udq,
/* AVX_vmaskmovpd1 */ &Ia_vmaskmovpd_Mpd_Hpd_Vpd,
/* AVX_vmaskmovpd2 */ &Ia_vmaskmovpd_Vpd_Hpd_Mpd,
/* AVX_vmaskmovps1 */ &Ia_vmaskmovps_Mps_Hps_Vps,
/* AVX_vmaskmovps2 */ &Ia_vmaskmovps_Vps_Hps_Mps,
/* AVX_vmaskmovq1 */ &Ia_vmaskmovq_Mdq_Hdq_Vdq,
/* AVX_vmaskmovq2 */ &Ia_vmaskmovq_Vdq_Hdq_Mdq,
/* AVX_vmaxpd */ &Ia_vmaxpd_Vpd_Hpd_Wpd,
/* AVX_vmaxps */ &Ia_vmaxps_Vps_Hps_Wps,
/* AVX_vmaxsd */ &Ia_vmaxsd_Vsd_Hpd_Wsd,
/* AVX_vmaxss */ &Ia_vmaxss_Vss_Hps_Wss,
/* AVX_vminpd */ &Ia_vminpd_Vpd_Hpd_Wpd,
/* AVX_vminps */ &Ia_vminps_Vps_Hps_Wps,
/* AVX_vminsd */ &Ia_vminsd_Vsd_Hpd_Wsd,
/* AVX_vminss */ &Ia_vminss_Vss_Hps_Wss,
/* AVX_vmovapd1 */ &Ia_vmovapd_Vpd_Wpd,
/* AVX_vmovapd2 */ &Ia_vmovapd_Wpd_Vpd,
/* AVX_vmovaps1 */ &Ia_vmovaps_Vps_Wps,
/* AVX_vmovaps2 */ &Ia_vmovaps_Wps_Vps,
/* AVX_vmovd1 */ &Ia_vmovd_Ed_Vd,
/* AVX_vmovd2 */ &Ia_vmovd_Vdq_Ed,
/* AVX_vmovddup */ &Ia_vmovddup_Vdq_Wq,
/* AVX_vmovdqa1 */ &Ia_vmovdqa_Vdq_Wdq,
/* AVX_vmovdqa2 */ &Ia_vmovdqa_Wdq_Vdq,
/* AVX_vmovdqu1 */ &Ia_vmovdqu_Vdq_Wdq,
/* AVX_vmovdqu2 */ &Ia_vmovdqu_Wdq_Vdq,
/* AVX_vmovhlpd */ &Ia_vmovhlpd_Vpd_Hdq_Udq,
/* AVX_vmovhlps */ &Ia_vmovhlps_Vps_Hdq_Udq,
/* AVX_vmovhpd1 */ &Ia_vmovhpd_Mq_Vpd,
/* AVX_vmovhpd2 */ &Ia_vmovhpd_Vpd_Hdq_Mq,
/* AVX_vmovhps1 */ &Ia_vmovhps_Mq_Vps,
/* AVX_vmovhps2 */ &Ia_vmovhps_Vps_Hdq_Mq,
/* AVX_vmovlhpd */ &Ia_vmovlhpd_Vpd_Hdq_Udq,
/* AVX_vmovlhps */ &Ia_vmovlhps_Vps_Hdq_Udq,
/* AVX_vmovlpd1 */ &Ia_vmovlpd_Mq_Vpd,
/* AVX_vmovlpd2 */ &Ia_vmovlpd_Vpd_Hdq_Mq,
/* AVX_vmovlps1 */ &Ia_vmovlps_Mq_Vps,
/* AVX_vmovlps2 */ &Ia_vmovlps_Vps_Hdq_Mq,
/* AVX_vmovmskpd */ &Ia_vmovmskpd_Gd_Vpd,
/* AVX_vmovmskps */ &Ia_vmovmskps_Gd_Vps,
/* AVX_vmovntdq */ &Ia_vmovntdq_Mdq_Vdq,
/* AVX_vmovntdqa */ &Ia_vmovntdqa_Vdq_Mdq,
/* AVX_vmovntpd */ &Ia_vmovntpd_Mpd_Vpd,
/* AVX_vmovntps */ &Ia_vmovntps_Mps_Vps,
/* AVX_vmovq1 */ &Ia_vmovq_Eq_Vq,
/* AVX_vmovq2 */ &Ia_vmovq_Vdq_Eq,
/* AVX_vmovq3 */ &Ia_vmovq_Vq_Wq,
/* AVX_vmovq4 */ &Ia_vmovq_Wq_Vq,
/* AVX_vmovsd1 */ &Ia_vmovsd_Vsd_Wsd,
/* AVX_vmovsd2 */ &Ia_vmovsd_Wsd_Vsd,
/* AVX_vmovshdup */ &Ia_vmovshdup_Vdq_Wdq,
/* AVX_vmovsldup */ &Ia_vmovsldup_Vdq_Wdq,
/* AVX_vmovss1 */ &Ia_vmovss_Vss_Wss,
/* AVX_vmovss2 */ &Ia_vmovss_Wss_Vss,
/* AVX_vmovupd1 */ &Ia_vmovupd_Vpd_Wpd,
/* AVX_vmovupd2 */ &Ia_vmovupd_Wpd_Vpd,
/* AVX_vmovups1 */ &Ia_vmovups_Vps_Wps,
/* AVX_vmovups2 */ &Ia_vmovups_Wps_Vps,
/* AVX_vmpsadbw */ &Ia_vmpsadbw_Vdq_Hdq_Wdq_Ib,
/* AVX_vmulpd */ &Ia_vmulpd_Vpd_Hpd_Wpd,
/* AVX_vmulps */ &Ia_vmulps_Vps_Hps_Wps,
/* AVX_vmulsd */ &Ia_vmulsd_Vsd_Hpd_Wsd,
/* AVX_vmulss */ &Ia_vmulss_Vss_Hps_Wss,
/* AVX_vorpd */ &Ia_vorpd_Vpd_Hpd_Wpd,
/* AVX_vorps */ &Ia_vorps_Vps_Hps_Wps,
/* AVX_vpabsb */ &Ia_vpabsb_Vdq_Hdq_Wdq,
/* AVX_vpabsd */ &Ia_vpabsd_Vdq_Hdq_Wdq,
/* AVX_vpabsw */ &Ia_vpabsw_Vdq_Hdq_Wdq,
/* AVX_vpackssdw */ &Ia_vpackssdw_Vdq_Hdq_Wdq,
/* AVX_vpacksswb */ &Ia_vpacksswb_Vdq_Hdq_Wdq,
/* AVX_vpackusdw */ &Ia_vpackusdw_Vdq_Hdq_Wdq,
/* AVX_vpackuswb */ &Ia_vpackuswb_Vdq_Hdq_Wdq,
/* AVX_vpaddb */ &Ia_vpaddb_Vdq_Hdq_Wdq,
/* AVX_vpaddd */ &Ia_vpaddd_Vdq_Hdq_Wdq,
/* AVX_vpaddq */ &Ia_vpaddq_Vdq_Hdq_Wdq,
/* AVX_vpaddsb */ &Ia_vpaddsb_Vdq_Hdq_Wdq,
/* AVX_vpaddsw */ &Ia_vpaddsw_Vdq_Hdq_Wdq,
/* AVX_vpaddusb */ &Ia_vpaddusb_Vdq_Hdq_Wdq,
/* AVX_vpaddusw */ &Ia_vpaddusw_Vdq_Hdq_Wdq,
/* AVX_vpaddw */ &Ia_vpaddw_Vdq_Hdq_Wdq,
/* AVX_vpalignr */ &Ia_vpalignr_Vdq_Hdq_Wdq_Ib,
/* AVX_vpand */ &Ia_vpand_Vdq_Hdq_Wdq,
/* AVX_vpandn */ &Ia_vpandn_Vdq_Hdq_Wdq,
/* AVX_vpavgb */ &Ia_vpavgb_Vdq_Hdq_Wdq,
/* AVX_vpavgw */ &Ia_vpavgw_Vdq_Hdq_Wdq,
/* AVX_vpblendd */ &Ia_vpblendd_Vdq_Hdq_Wdq_Ib,
/* AVX_vpblendvb */ &Ia_vpblendvb_Vdq_Hdq_Wdq_Ib,
/* AVX_vpblendw */ &Ia_vpblendw_Vdq_Hdq_Wdq_Ib,
/* AVX_vpbroadcastb */ &Ia_vpbroadcastb_Vdq_Wb,
/* AVX_vpbroadcastd */ &Ia_vpbroadcastd_Vdq_Wd,
/* AVX_vpbroadcastq */ &Ia_vpbroadcastq_Vdq_Wq,
/* AVX_vpbroadcastw */ &Ia_vpbroadcastw_Vdq_Ww,
/* AVX_vpclmulqdq */ &Ia_vpclmulqdq_Vdq_Hdq_Wdq_Ib,
/* AVX_vpcmpeqb */ &Ia_vpcmpeqb_Vdq_Hdq_Wdq,
/* AVX_vpcmpeqd */ &Ia_vpcmpeqd_Vdq_Hdq_Wdq,
/* AVX_vpcmpeqq */ &Ia_vpcmpeqq_Vdq_Hdq_Wdq,
/* AVX_vpcmpeqw */ &Ia_vpcmpeqw_Vdq_Hdq_Wdq,
/* AVX_vpcmpestri */ &Ia_vpcmpestri_Vdq_Wdq_Ib,
/* AVX_vpcmpestrm */ &Ia_vpcmpestrm_Vdq_Wdq_Ib,
/* AVX_vpcmpgtb */ &Ia_vpcmpgtb_Vdq_Hdq_Wdq,
/* AVX_vpcmpgtd */ &Ia_vpcmpgtd_Vdq_Hdq_Wdq,
/* AVX_vpcmpgtq */ &Ia_vpcmpgtq_Vdq_Hdq_Wdq,
/* AVX_vpcmpgtw */ &Ia_vpcmpgtw_Vdq_Hdq_Wdq,
/* AVX_vpcmpistri */ &Ia_vpcmpistri_Vdq_Wdq_Ib,
/* AVX_vpcmpistrm */ &Ia_vpcmpistrm_Vdq_Wdq_Ib,
/* AVX_vperm2f128 */ &Ia_vperm2f128_Vdq_Hdq_Wdq_Ib,
/* AVX_vperm2128 */ &Ia_vperm2i128_Vdq_Hdq_Wdq_Ib,
/* AVX_vpermd */ &Ia_vpermd_Vdq_Hdq_Wdq,
/* AVX_vpermilpd1 */ &Ia_vpermilpd_Vpd_Hpd_Wpd,
/* AVX_vpermilpd2 */ &Ia_vpermilpd_Vpd_Wpd_Ib,
/* AVX_vpermilps1 */ &Ia_vpermilps_Vps_Hps_Wps,
/* AVX_vpermilps2 */ &Ia_vpermilps_Vps_Wps_Ib,
/* AVX_vpermpd */ &Ia_vpermpd_Vpd_Wpd_Ib,
/* AVX_vpermps */ &Ia_vpermps_Vps_Hps_Wps,
/* AVX_vpermq */ &Ia_vpermq_Vdq_Wdq_Ib,
/* AVX_vpextrb */ &Ia_vpextrb_Ebd_Vdq_Ib,
/* AVX_vpextrd */ &Ia_vpextrd_Ed_Vdq_Ib,
/* AVX_vpextrq */ &Ia_vpextrq_Eq_Vdq_Ib,
/* AVX_vpextrw1 */ &Ia_vpextrw_Ewd_Vdq_Ib,
/* AVX_vpextrw2 */ &Ia_vpextrw_Gd_Udq_Ib,
/* AVX_vphaddd */ &Ia_vphaddd_Vdq_Hdq_Wdq,
/* AVX_vphaddsw */ &Ia_vphaddsw_Vdq_Hdq_Wdq,
/* AVX_vphaddw */ &Ia_vphaddw_Vdq_Hdq_Wdq,
/* AVX_vphminposuw */ &Ia_vphminposuw_Vdq_Wdq,
/* AVX_vphsubd */ &Ia_vphsubd_Vdq_Hdq_Wdq,
/* AVX_vphsubsw */ &Ia_vphsubsw_Vdq_Hdq_Wdq,
/* AVX_vphsubw */ &Ia_vphsubw_Vdq_Hdq_Wdq,
/* AVX_vpinsrb */ &Ia_vpinsrb_Vdq_Hdq_Ed_Ib,
/* AVX_vpinsrd */ &Ia_vpinsrd_Vdq_Hdq_Ed_Ib,
/* AVX_vpinsrq */ &Ia_vpinsrq_Vdq_Hdq_Eq_Ib,
/* AVX_vpinsrw */ &Ia_vpinsrw_Vdq_Hdq_Ew_Ib,
/* AVX_vpmaddubsw */ &Ia_vpmaddubsw_Vdq_Hdq_Wdq,
/* AVX_vpmaddwd */ &Ia_vpmaddwd_Vdq_Hdq_Wdq,
/* AVX_vpmaxsb */ &Ia_vpmaxsb_Vdq_Hdq_Wdq,
/* AVX_vpmaxsd */ &Ia_vpmaxsd_Vdq_Hdq_Wdq,
/* AVX_vpmaxsw */ &Ia_vpmaxsw_Vdq_Hdq_Wdq,
/* AVX_vpmaxub */ &Ia_vpmaxub_Vdq_Hdq_Wdq,
/* AVX_vpmaxud */ &Ia_vpmaxud_Vdq_Hdq_Wdq,
/* AVX_vpmaxuw */ &Ia_vpmaxuw_Vdq_Hdq_Wdq,
/* AVX_vpminsb */ &Ia_vpminsb_Vdq_Hdq_Wdq,
/* AVX_vpminsd */ &Ia_vpminsd_Vdq_Hdq_Wdq,
/* AVX_vpminsw */ &Ia_vpminsw_Vdq_Hdq_Wdq,
/* AVX_vpminub */ &Ia_vpminub_Vdq_Hdq_Wdq,
/* AVX_vpminud */ &Ia_vpminud_Vdq_Hdq_Wdq,
/* AVX_vpminuw */ &Ia_vpminuw_Vdq_Hdq_Wdq,
/* AVX_vpmovmskb */ &Ia_vpmovmskb_Gd_Udq,
/* AVX_vpmovsxbd */ &Ia_vpmovsxbd_Vdq_Wd,
/* AVX_vpmovsxbq */ &Ia_vpmovsxbq_Vdq_Ww,
/* AVX_vpmovsxbw */ &Ia_vpmovsxbw_Vdq_Wq,
/* AVX_vpmovsxdq */ &Ia_vpmovsxdq_Vdq_Wq,
/* AVX_vpmovsxwd */ &Ia_vpmovsxwd_Vdq_Wq,
/* AVX_vpmovsxwq */ &Ia_vpmovsxwq_Vdq_Wd,
/* AVX_vpmovzxbd */ &Ia_vpmovzxbd_Vdq_Wd,
/* AVX_vpmovzxbq */ &Ia_vpmovzxbq_Vdq_Ww,
/* AVX_vpmovzxbw */ &Ia_vpmovzxbw_Vdq_Wq,
/* AVX_vpmovzxdq */ &Ia_vpmovzxdq_Vdq_Wq,
/* AVX_vpmovzxwd */ &Ia_vpmovzxwd_Vdq_Wq,
/* AVX_vpmovzxwq */ &Ia_vpmovzxwq_Vdq_Wd,
/* AVX_vpmuldq */ &Ia_vpmuldq_Vdq_Hdq_Wdq,
/* AVX_vpmulhrsw */ &Ia_vpmulhrsw_Vdq_Hdq_Wdq,
/* AVX_vpmulhuw */ &Ia_vpmulhuw_Vdq_Hdq_Wdq,
/* AVX_vpmulhw */ &Ia_vpmulhw_Vdq_Hdq_Wdq,
/* AVX_vpmulld */ &Ia_vpmulld_Vdq_Hdq_Wdq,
/* AVX_vpmullw */ &Ia_vpmullw_Vdq_Hdq_Wdq,
/* AVX_vpmuludq */ &Ia_vpmuludq_Vdq_Hdq_Wdq,
/* AVX_vpor */ &Ia_vpor_Vdq_Hdq_Wdq,
/* AVX_vpsadbw */ &Ia_vpsadbw_Vdq_Hdq_Wdq,
/* AVX_vpshufb */ &Ia_vpshufb_Vdq_Hdq_Wdq,
/* AVX_vpshufd */ &Ia_vpshufd_Vdq_Hdq_Wdq_Ib,
/* AVX_vpshufhw */ &Ia_vpshufhw_Vdq_Hdq_Wdq_Ib,
/* AVX_vpshuflw */ &Ia_vpshuflw_Vdq_Hdq_Wdq_Ib,
/* AVX_vpsignb */ &Ia_vpsignb_Vdq_Hdq_Wdq,
/* AVX_vpsignd */ &Ia_vpsignd_Vdq_Hdq_Wdq,
/* AVX_vpsignw */ &Ia_vpsignw_Vdq_Hdq_Wdq,
/* AVX_vpslld1 */ &Ia_vpslld_Hdq_Udq_Ib,
/* AVX_vpslld2 */ &Ia_vpslld_Vdq_Hdq_Wdq,
/* AVX_vpslldq */ &Ia_vpslldq_Hdq_Udq_Ib,
/* AVX_vpsllq1 */ &Ia_vpsllq_Hdq_Udq_Ib,
/* AVX_vpsllq2 */ &Ia_vpsllq_Vdq_Hdq_Wdq,
/* AVX_vpsllvd */ &Ia_vpsllvd_Vdq_Hdq_Wdq,
/* AVX_vpsllvq */ &Ia_vpsllvq_Vdq_Hdq_Wdq,
/* AVX_vpsllw1 */ &Ia_vpsllw_Hdq_Udq_Ib,
/* AVX_vpsllw2 */ &Ia_vpsllw_Vdq_Hdq_Wdq,
/* AVX_vpsrad1 */ &Ia_vpsrad_Hdq_Udq_Ib,
/* AVX_vpsrad2 */ &Ia_vpsrad_Vdq_Hdq_Wdq,
/* AVX_vpsravd */ &Ia_vpsravd_Vdq_Hdq_Wdq,
/* AVX_vpsraw1 */ &Ia_vpsraw_Hdq_Udq_Ib,
/* AVX_vpsraw2 */ &Ia_vpsraw_Vdq_Hdq_Wdq,
/* AVX_vpsrld1 */ &Ia_vpsrld_Hdq_Udq_Ib,
/* AVX_vpsrld2 */ &Ia_vpsrld_Vdq_Hdq_Wdq,
/* AVX_vpsrldq */ &Ia_vpsrldq_Hdq_Udq_Ib,
/* AVX_vpsrlq1 */ &Ia_vpsrlq_Hdq_Udq_Ib,
/* AVX_vpsrlq2 */ &Ia_vpsrlq_Vdq_Hdq_Wdq,
/* AVX_vpsrlvd */ &Ia_vpsrlvd_Vdq_Hdq_Wdq,
/* AVX_vpsrlvq */ &Ia_vpsrlvq_Vdq_Hdq_Wdq,
/* AVX_vpsrlw1 */ &Ia_vpsrlw_Hdq_Udq_Ib,
/* AVX_vpsrlw2 */ &Ia_vpsrlw_Vdq_Hdq_Wdq,
/* AVX_vpsubb */ &Ia_vpsubb_Vdq_Hdq_Wdq,
/* AVX_vpsubd */ &Ia_vpsubd_Vdq_Hdq_Wdq,
/* AVX_vpsubq */ &Ia_vpsubq_Vdq_Hdq_Wdq,
/* AVX_vpsubsb */ &Ia_vpsubsb_Vdq_Hdq_Wdq,
/* AVX_vpsubsw */ &Ia_vpsubsw_Vdq_Hdq_Wdq,
/* AVX_vpsubusb */ &Ia_vpsubusb_Vdq_Hdq_Wdq,
/* AVX_vpsubusw */ &Ia_vpsubusw_Vdq_Hdq_Wdq,
/* AVX_vpsubw */ &Ia_vpsubw_Vdq_Hdq_Wdq,
/* AVX_vptest */ &Ia_vptest_Vdq_Wdq,
/* AVX_vpunpckhbw */ &Ia_vpunpckhbw_Vdq_Hdq_Wdq,
/* AVX_vpunpckhdq */ &Ia_vpunpckhdq_Vdq_Hdq_Wdq,
/* AVX_vpunpckhqdq */ &Ia_vpunpckhqdq_Vdq_Hdq_Wdq,
/* AVX_vpunpckhwd */ &Ia_vpunpckhwd_Vdq_Hdq_Wdq,
/* AVX_vpunpcklbw */ &Ia_vpunpcklbw_Vdq_Hdq_Wdq,
/* AVX_vpunpckldq */ &Ia_vpunpckldq_Vdq_Hdq_Wdq,
/* AVX_vpunpcklqdq */ &Ia_vpunpcklqdq_Vdq_Hdq_Wdq,
/* AVX_vpunpcklwd */ &Ia_vpunpcklwd_Vdq_Hdq_Wdq,
/* AVX_vpxor */ &Ia_vpxor_Vdq_Hdq_Wdq,
/* AVX_vrcpps */ &Ia_vrcpps_Vps_Wps,
/* AVX_vrcpss */ &Ia_vrcpss_Vss_Hps_Wss,
/* AVX_vroundpd */ &Ia_vroundpd_Vpd_Wpd_Ib,
/* AVX_vroundps */ &Ia_vroundps_Vps_Wps_Ib,
/* AVX_vroundsd */ &Ia_vroundsd_Vsd_Hpd_Wsd_Ib,
/* AVX_vroundss */ &Ia_vroundss_Vss_Hps_Wss_Ib,
/* AVX_vrsqrtps */ &Ia_vrsqrtps_Vps_Wps,
/* AVX_vrsqrtss */ &Ia_vrsqrtss_Vss_Hps_Wss,
/* AVX_vshufpd */ &Ia_vshufpd_Vpd_Hpd_Wpd_Ib,
/* AVX_vshufps */ &Ia_vshufps_Vps_Hps_Wps_Ib,
/* AVX_vsqrtpd */ &Ia_vsqrtpd_Vpd_Wpd,
/* AVX_vsqrtps */ &Ia_vsqrtps_Vps_Wps,
/* AVX_vsqrtsd */ &Ia_vsqrtsd_Vsd_Hpd_Wsd,
/* AVX_vsqrtss */ &Ia_vsqrtss_Vss_Hps_Wss,
/* AVX_vstmxcsr */ &Ia_vstmxcsr,
/* AVX_vsubpd */ &Ia_vsubpd_Vpd_Hpd_Wpd,
/* AVX_vsubps */ &Ia_vsubps_Vps_Hps_Wps,
/* AVX_vsubsd */ &Ia_vsubsd_Vsd_Hpd_Wsd,
/* AVX_vsubss */ &Ia_vsubss_Vss_Hps_Wss,
/* AVX_vtestpd */ &Ia_vtestpd_Vpd_Wpd,
/* AVX_vtestps */ &Ia_vtestps_Vps_Wps,
/* AVX_vucomisd */ &Ia_vucomisd_Vsd_Wsd,
/* AVX_vucomiss */ &Ia_vucomiss_Vss_Wss,
/* AVX_vunpckhpd */ &Ia_vunpckhpd_Vpd_Hpd_Wpd,
/* AVX_vunpckhps */ &Ia_vunpckhps_Vps_Hps_Wps,
/* AVX_vunpcklpd */ &Ia_vunpcklpd_Vpd_Hpd_Wpd,
/* AVX_vunpcklps */ &Ia_vunpcklps_Vps_Hps_Wps,
/* AVX_vxorpd */ &Ia_vxorpd_Vpd_Hpd_Wpd,
/* AVX_vxorps */ &Ia_vxorps_Vps_Hps_Wps,
/* AVX_vzeroall */ &Ia_vzerall,
/* AVX_vzeroupper */ &Ia_vzeroupper,
/* AVX_frczpd */ &Ia_frczpd_Vpd_Wpd,
/* AVX_frczps */ &Ia_frczps_Vps_Wps,
/* AVX_frczsd */ &Ia_frczsd_Vsd_Wsd,
/* AVX_frczss */ &Ia_frczss_Vss_Wss,
/* AVX_vpcmov1 */ &Ia_vpcmov_Vdq_Hdq_VIb_Wdq,
/* AVX_vpcmov2 */ &Ia_vpcmov_Vdq_Hdq_Wdq_VIb,
/* AVX_vpcomb */ &Ia_vpcomb_Vdq_Hdq_Wdq_Ib,
/* AVX_vpcomd */ &Ia_vpcomd_Vdq_Hdq_Wdq_Ib,
/* AVX_vpcomq */ &Ia_vpcomq_Vdq_Hdq_Wdq_Ib,
/* AVX_vpcomub */ &Ia_vpcomub_Vdq_Hdq_Wdq_Ib,
/* AVX_vpcomud */ &Ia_vpcomud_Vdq_Hdq_Wdq_Ib,
/* AVX_vpcomuq */ &Ia_vpcomuq_Vdq_Hdq_Wdq_Ib,
/* AVX_vpcomuw */ &Ia_vpcomuw_Vdq_Hdq_Wdq_Ib,
/* AVX_vpcomw */ &Ia_vpcomw_Vdq_Hdq_Wdq_Ib,
/* AVX_vphaddbd */ &Ia_vphaddbd_Vdq_Wdq,
/* AVX_vphaddbq */ &Ia_vphaddbq_Vdq_Wdq,
/* AVX_vphaddbw */ &Ia_vphaddbw_Vdq_Wdq,
/* AVX_vphadddq */ &Ia_vphadddq_Vdq_Wdq,
/* AVX_vphaddubd */ &Ia_vphaddubd_Vdq_Wdq,
/* AVX_vphaddubq */ &Ia_vphaddubq_Vdq_Wdq,
/* AVX_vphaddubw */ &Ia_vphaddubw_Vdq_Wdq,
/* AVX_vphaddudq */ &Ia_vphaddudq_Vdq_Wdq,
/* AVX_vphadduwd */ &Ia_vphadduwd_Vdq_Wdq,
/* AVX_vphadduwq */ &Ia_vphadduwq_Vdq_Wdq,
/* AVX_vphaddwd */ &Ia_vphaddwd_Vdq_Wdq,
/* AVX_vphaddwq */ &Ia_vphaddwq_Vdq_Wdq,
/* AVX_vphsubbw */ &Ia_vphsubbw_Vdq_Wdq,
/* AVX_vphsubdq */ &Ia_vphsubdq_Vdq_Wdq,
/* AVX_vphsubwd */ &Ia_vphsubwd_Vdq_Wdq,
/* AVX_vpmacsdd */ &Ia_vpmacsdd_Vdq_Hdq_Wdq_VIb,
/* AVX_vpmacsdqh */ &Ia_vpmacsdqh_Vdq_Hdq_Wdq_VIb,
/* AVX_vpmacsdql */ &Ia_vpmacsdql_Vdq_Hdq_Wdq_VIb,
/* AVX_vpmacssdd */ &Ia_vpmacssdd_Vdq_Hdq_Wdq_VIb,
/* AVX_vpmacssdqh */ &Ia_vpmacssdqh_Vdq_Hdq_Wdq_VIb,
/* AVX_vpmacssdql */ &Ia_vpmacssdql_Vdq_Hdq_Wdq_VIb,
/* AVX_vpmacsswd */ &Ia_vpmacsswd_Vdq_Hdq_Wdq_VIb,
/* AVX_vpmacssww */ &Ia_vpmacssww_Vdq_Hdq_Wdq_VIb,
/* AVX_vpmacswd */ &Ia_vpmacswd_Vdq_Hdq_Wdq_VIb,
/* AVX_vpmacsww */ &Ia_vpmacsww_Vdq_Hdq_Wdq_VIb,
/* AVX_vpmadcsswd */ &Ia_vpmadcsswd_Vdq_Hdq_Wdq_VIb,
/* AVX_vpmadcswd */ &Ia_vpmadcswd_Vdq_Hdq_Wdq_VIb,
/* AVX_vpperm1 */ &Ia_vpperm_Vdq_Hdq_VIb_Wdq,
/* AVX_vpperm2 */ &Ia_vpperm_Vdq_Hdq_Wdq_VIb,
/* AVX_vprotb1 */ &Ia_vprotb_Vdq_Hdq_Wdq,
/* AVX_vprotb2 */ &Ia_vprotb_Vdq_Wdq_Hdq,
/* AVX_vprotb3 */ &Ia_vprotb_Vdq_Wdq_Ib,
/* AVX_vprotd1 */ &Ia_vprotd_Vdq_Hdq_Wdq,
/* AVX_vprotd2 */ &Ia_vprotd_Vdq_Wdq_Hdq,
/* AVX_vprotd3 */ &Ia_vprotd_Vdq_Wdq_Ib,
/* AVX_vprotq1 */ &Ia_vprotq_Vdq_Hdq_Wdq,
/* AVX_vprotq2 */ &Ia_vprotq_Vdq_Wdq_Hdq,
/* AVX_vprotq3 */ &Ia_vprotq_Vdq_Wdq_Ib,
/* AVX_vprotw1 */ &Ia_vprotw_Vdq_Hdq_Wdq,
/* AVX_vprotw2 */ &Ia_vprotw_Vdq_Wdq_Hdq,
/* AVX_vprotw3 */ &Ia_vprotw_Vdq_Wdq_Ib,
/* AVX_vpshab1 */ &Ia_vpshab_Vdq_Hdq_Wdq,
/* AVX_vpshab2 */ &Ia_vpshab_Vdq_Wdq_Hdq,
/* AVX_vpshad1 */ &Ia_vpshad_Vdq_Hdq_Wdq,
/* AVX_vpshad2 */ &Ia_vpshad_Vdq_Wdq_Hdq,
/* AVX_vpshaq1 */ &Ia_vpshaq_Vdq_Hdq_Wdq,
/* AVX_vpshaq2 */ &Ia_vpshaq_Vdq_Wdq_Hdq,
/* AVX_vpshaw1 */ &Ia_vpshaw_Vdq_Hdq_Wdq,
/* AVX_vpshaw2 */ &Ia_vpshaw_Vdq_Wdq_Hdq,
/* AVX_vpshlb1 */ &Ia_vpshlb_Vdq_Hdq_Wdq,
/* AVX_vpshlb2 */ &Ia_vpshlb_Vdq_Wdq_Hdq,
/* AVX_vpshld1 */ &Ia_vpshld_Vdq_Hdq_Wdq,
/* AVX_vpshld2 */ &Ia_vpshld_Vdq_Wdq_Hdq,
/* AVX_vpshlq1 */ &Ia_vpshlq_Vdq_Hdq_Wdq,
/* AVX_vpshlq2 */ &Ia_vpshlq_Vdq_Wdq_Hdq,
/* AVX_vpshlw1 */ &Ia_vpshlw_Vdq_Hdq_Wdq,
/* AVX_vpshlw2 */ &Ia_vpshlw_Vdq_Wdq_Hdq,
/* AVX_andn */ &Ia_andn_Gy_By_Ey,
/* AVX_bextr1 */ &Ia_bextr_Gy_Ey_By,
/* AVX_blsi */ &Ia_blsi_By_Ey,
/* AVX_blsmsk */ &Ia_blsmsk_By_Ey,
/* AVX_blsr */ &Ia_blsr_By_Ey,
/* AVX_bzhi */ &Ia_bzhi_Gy_Ey_By,
/* AVX_mulx */ &Ia_mulx_By_Gy_Ey,
/* AVX_pdep */ &Ia_pdep_Gy_By_Ey,
/* AVX_pext */ &Ia_pext_Gy_By_Ey,
/* AVX_rorx */ &Ia_rorx_Gy_Ey_Ib,
/* AVX_sarx */ &Ia_sarx_Gy_Ey_By,
/* AVX_shlx */ &Ia_shlx_Gy_Ey_By,
/* AVX_shrx */ &Ia_shrx_Gy_Ey_By,
/* AVX_tzcntl */ &Ia_tzcntl_Gd_Ed,
/* AVX_tzcntq */ &Ia_tzcntq_Gq_Eq,
/* AVX_tzcntw */ &Ia_tzcntw_Gw_Ew,
/* AVX_vfmaddpd1 */ &Ia_vfmaddpd_Vpd_Hpd_VIb_Wpd,
/* AVX_vfmaddpd2 */ &Ia_vfmaddpd_Vpd_Hpd_Wpd_VIb,
/* AVX_vfmaddps1 */ &Ia_vfmaddps_Vps_Hps_VIb_Wps,
/* AVX_vfmaddps2 */ &Ia_vfmaddps_Vps_Hps_Wps_VIb,
/* AVX_vfmaddsd1 */ &Ia_vfmaddsd_Vsd_Hsd_VIb_Wsd,
/* AVX_vfmaddsd2 */ &Ia_vfmaddsd_Vsd_Hsd_Wsd_VIb,
/* AVX_vfmaddss1 */ &Ia_vfmaddss_Vss_Hss_VIb_Wss,
/* AVX_vfmaddss2 */ &Ia_vfmaddss_Vss_Hss_Wss_VIb,
/* AVX_vfmaddsubpd1 */ &Ia_vfmaddsubpd_Vpd_Hpd_VIb_Wpd,
/* AVX_vfmaddsubpd2 */ &Ia_vfmaddsubpd_Vpd_Hpd_Wpd_VIb,
/* AVX_vfmaddsubps1 */ &Ia_vfmaddsubps_Vps_Hps_VIb_Wps,
/* AVX_vfmaddsubps2 */ &Ia_vfmaddsubps_Vps_Hps_Wps_VIb,
/* AVX_vfmsubaddpd1 */ &Ia_vfmsubaddpd_Vpd_Hpd_VIb_Wpd,
/* AVX_vfmsubaddpd2 */ &Ia_vfmsubaddpd_Vpd_Hpd_Wpd_VIb,
/* AVX_vfmsubaddps1 */ &Ia_vfmsubaddps_Vps_Hps_VIb_Wps,
/* AVX_vfmsubaddps2 */ &Ia_vfmsubaddps_Vps_Hps_Wps_VIb,
/* AVX_vfmsubpd1 */ &Ia_vfmsubpd_Vpd_Hpd_VIb_Wpd,
/* AVX_vfmsubpd2 */ &Ia_vfmsubpd_Vpd_Hpd_Wpd_VIb,
/* AVX_vfmsubps1 */ &Ia_vfmsubps_Vps_Hps_VIb_Wps,
/* AVX_vfmsubps2 */ &Ia_vfmsubps_Vps_Hps_Wps_VIb,
/* AVX_vfmsubsd1 */ &Ia_vfmsubsd_Vsd_Hsd_VIb_Wsd,
/* AVX_vfmsubsd2 */ &Ia_vfmsubsd_Vsd_Hsd_Wsd_VIb,
/* AVX_vfmsubss1 */ &Ia_vfmsubss_Vss_Hss_VIb_Wss,
/* AVX_vfmsubss2 */ &Ia_vfmsubss_Vss_Hss_Wss_VIb,
/* AVX_vfnmaddpd1 */ &Ia_vfnmaddpd_Vpd_Hpd_VIb_Wpd,
/* AVX_vfnmaddpd2 */ &Ia_vfnmaddpd_Vpd_Hpd_Wpd_VIb,
/* AVX_vfnmaddps1 */ &Ia_vfnmaddps_Vps_Hps_VIb_Wps,
/* AVX_vfnmaddps2 */ &Ia_vfnmaddps_Vps_Hps_Wps_VIb,
/* AVX_vfnmaddsd1 */ &Ia_vfnmaddsd_Vsd_Hsd_VIb_Wsd,
/* AVX_vfnmaddsd2 */ &Ia_vfnmaddsd_Vsd_Hsd_Wsd_VIb,
/* AVX_vfnmaddss1 */ &Ia_vfnmaddss_Vss_Hss_VIb_Wss,
/* AVX_vfnmaddss2 */ &Ia_vfnmaddss_Vss_Hss_Wss_VIb,
/* AVX_vfnmsubpd1 */ &Ia_vfnmsubpd_Vpd_Hpd_VIb_Wpd,
/* AVX_vfnmsubpd2 */ &Ia_vfnmsubpd_Vpd_Hpd_Wpd_VIb,
/* AVX_vfnmsubps1 */ &Ia_vfnmsubps_Vps_Hps_VIb_Wps,
/* AVX_vfnmsubps2 */ &Ia_vfnmsubps_Vps_Hps_Wps_VIb,
/* AVX_vfnmsubsd1 */ &Ia_vfnmsubsd_Vsd_Hsd_VIb_Wsd,
/* AVX_vfnmsubsd2 */ &Ia_vfnmsubsd_Vsd_Hsd_Wsd_VIb,
/* AVX_vfnmsubss1 */ &Ia_vfnmsubss_Vss_Hss_VIb_Wss,
/* AVX_vfnmsubss2 */ &Ia_vfnmsubss_Vss_Hss_Wss_VIb,
/* AVX_bextr2 */ &Ia_bextr_Gy_Ey_Id,
/* AVX_blcfill */ &Ia_blcfill_By_Ey,
/* AVX_blci */ &Ia_blci_By_Ey,
/* AVX_blcic */ &Ia_blcic_By_Ey,
/* AVX_blcmsk */ &Ia_blcmsk_By_Ey,
/* AVX_blcs */ &Ia_blcs_By_Ey,
/* AVX_blsfill */ &Ia_blsfill_By_Ey,
/* AVX_blsic */ &Ia_blsic_By_Ey,
/* AVX_t1mskc */ &Ia_t1mskc_By_Ey,
/* AVX_tzmsk */ &Ia_tzmsk_By_Ey,
};
