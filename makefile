main:
	gcc -g shell.c prompt.c exec_cmd.c cd.c echo.c pwd.c ls.c pinfo.c exec_vp.c history.c nightswatch.c redirect.c jobs.c procs.c env.c pipe.c logical.c


# objects = shell prompt exec_cmd exec_vp pwd ls pinfo history nightswatch redirect cd env echo procs jobs
# all: $(objects)

# $(objects): %: %.c
# 	$(CC) $(CFLAGS) -o $@ $<