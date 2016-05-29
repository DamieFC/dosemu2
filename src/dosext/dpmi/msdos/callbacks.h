#ifndef CALLBACKS_H
#define CALLBACKS_H

void msdos_api_call(struct sigcontext *scp, void *arg);
void msdos_api_winos2_call(struct sigcontext *scp, void *arg);
void xms_call(struct RealModeCallStructure *rmreg, void *arg);

void rm_do_int_to(u_short flags, u_short cs, u_short ip,
	struct RealModeCallStructure *rmreg,
	int *r_rmask, u_char *stk, int stk_len, int *stk_used);
void rm_int(int intno, u_short flags,
	struct RealModeCallStructure *rmreg,
	int *r_rmask, u_char *stk, int stk_len, int *stk_used);

void set_io_buffer(dosaddr_t ptr, unsigned int size);
void unset_io_buffer(void);
int is_io_error(uint16_t *r_code);

void callbacks_init(void *(*cbk_args)(int), far_t *r_cbks);

#ifdef DOSEMU
#define RMREG(r) (rmreg->r)
#define RMLWORD(r) (rmreg->e##r)
#define E_RMREG(r) (rmreg->r)
#endif
/* pre_extender() is allowed to read only a small set of rmregs, check mask */
#define READ_RMREG(r, m) (assert(m & (1 << r##_INDEX)), RMREG(r))
#define ip_INDEX eip_INDEX
#define sp_INDEX esp_INDEX
#define flags_INDEX eflags_INDEX
#define RM_LO(r) LO_BYTE(RMLWORD(r))

enum { RMCB_IO, RMCB_MS, RMCB_PS2MS, MAX_RMCBS };

#endif