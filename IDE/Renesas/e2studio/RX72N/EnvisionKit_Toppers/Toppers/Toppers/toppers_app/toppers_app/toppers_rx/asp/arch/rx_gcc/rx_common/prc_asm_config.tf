$
$     asm_config.inc 生成用
$     パス2のアーキテクチャ依存テンプレート（rx用）
$

$FILE "asm_config.inc"$


#define TIPM_LOCK $TAB$$TAB$ $TAB$ $+TIPM_LOCK$ $NL$
#define IPL_LOCK $TAB$$TAB$ $TAB$ $+IPL_LOCK$ $NL$
#define PSW_I_MASK $TAB$$TAB$ $TAB$ $+PSW_I_MASK$ $NL$
#define PSW_IPL_MASK $TAB$$TAB$ $TAB$ $+PSW_IPL_MASK$ $NL$
#define EXC_GET_PSW_OFFSET $TAB$$TAB$ $TAB$ $+EXC_GET_PSW_OFFSET$ $NL$
