/*
 * note "libubox-sample-runqueue" related file
 * Copyright (C) 2019 Dramalife <dramalife@live.com>
 * 
 * This file is part of [note](https://github.com/Dramalife/note.git)
 * 
 * note is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $ gcc --version
 * gcc (Ubuntu 5.5.0-12ubuntu1) 5.5.0 20171010
 * Copyright (C) 2015 Free Software Foundation, Inc.
 * This is free software; see the source for copying conditions.  There is NO
 * warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * 
 * ;
 * 
 * $ uname -a
 * Linux server 4.15.0-99-generic #100-Ubuntu SMP Wed Apr 22 20:32:56 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
 * ;
 * 
 * Init : Tue May 12 10:55:42 CST 2020
 * 	COPY FROM : libubox-2018-11-16-4382c76d/examples;
 * Update : Tue May 12 10:55:42 CST 2020
 * 	Change global variable name (p => gv_queue);
 *  
 * Update
 *
 */



/*
 * runqueue-example.c
 *
 * Copyright (C) 2013 Felix Fietkau <nbd@openwrt.org>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "uloop.h"
#include "runqueue.h"

static struct runqueue gv_queue;

struct sleeper {
	struct runqueue_process proc;
	int val;
};

static void q_empty(struct runqueue *q)
{
	fprintf(stderr, "All done!\n");
	uloop_end();
}

static void q_sleep_run(struct runqueue *q, struct runqueue_task *t)
{
	struct sleeper *s = container_of(t, struct sleeper, proc.task);
	char str[32];
	pid_t pid;

	fprintf(stderr, "[%d/%d] start 'sleep %d'\n", q->running_tasks, q->max_running_tasks, s->val);

	pid = fork();
	if (pid < 0)
		return;

	if (pid) {
		runqueue_process_add(q, &s->proc, pid);
		return;
	}

	sprintf(str, "%d", s->val);
	execlp("sleep", "sleep", str, NULL);
	exit(1);
}

static void q_sleep_cancel(struct runqueue *q, struct runqueue_task *t, int type)
{
	struct sleeper *s = container_of(t, struct sleeper, proc.task);

	fprintf(stderr, "[%d/%d] cancel 'sleep %d'\n", q->running_tasks, q->max_running_tasks, s->val);
	runqueue_process_cancel_cb(q, t, type);
}

static void q_sleep_complete(struct runqueue *q, struct runqueue_task *p)
{
	struct sleeper *s = container_of(p, struct sleeper, proc.task);

	fprintf(stderr, "[%d/%d] finish 'sleep %d'\n", q->running_tasks, q->max_running_tasks, s->val);
	free(s);
}

static void add_sleeper(int val)
{
	static const struct runqueue_task_type sleeper_type = {
		.run = q_sleep_run,
		.cancel = q_sleep_cancel,
		.kill = runqueue_process_kill_cb,
	};
	struct sleeper *s;

	s = calloc(1, sizeof(*s));
	s->proc.task.type = &sleeper_type;
	s->proc.task.run_timeout = 500;
	s->proc.task.complete = q_sleep_complete;
	s->val = val;
	runqueue_task_add(&gv_queue, &s->proc.task, false);
}

int main(int argc, char **argv)
{
	uloop_init();

	runqueue_init(&gv_queue);
	gv_queue.empty_cb = q_empty;
	gv_queue.max_running_tasks = 1;

	if (argc > 1)
		gv_queue.max_running_tasks = atoi(argv[1]);

	add_sleeper(1);
	add_sleeper(1);
	add_sleeper(1);
	uloop_run();
	uloop_done();

	return 0;
}
