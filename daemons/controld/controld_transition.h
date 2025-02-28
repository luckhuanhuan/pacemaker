/*
 * Copyright 2004-2022 the Pacemaker project contributors
 *
 * This source code is licensed under the GNU Lesser General Public License
 * version 2.1 or later (LGPLv2.1+) WITHOUT ANY WARRANTY.
 */

#ifndef TENGINE__H
#  define TENGINE__H

#  include <crm/common/mainloop.h>
#  include <crm/stonith-ng.h>
#  include <crm/services.h>
#  include <pacemaker-internal.h>

/* tengine */
pcmk__graph_action_t *match_down_event(const char *target);
pcmk__graph_action_t *get_cancel_action(const char *id, const char *node);
bool confirm_cancel_action(const char *id, const char *node_id);

void controld_record_action_timeout(pcmk__graph_action_t *action);
gboolean fail_incompletable_actions(pcmk__graph_t *graph, const char *down_node);
void process_graph_event(xmlNode *event, const char *event_node);

/* utils */
pcmk__graph_action_t *controld_get_action(int id);
gboolean stop_te_timer(pcmk__graph_action_t *action);
const char *get_rsc_state(const char *task, enum pcmk_exec_status status);

void process_te_message(xmlNode *msg, xmlNode *xml_data);

extern pcmk__graph_t *transition_graph;
extern crm_trigger_t *transition_trigger;

extern char *te_uuid;

void notify_crmd(pcmk__graph_t * graph);

void cib_action_updated(xmlNode *msg, int call_id, int rc, xmlNode *output,
                        void *user_data);
gboolean action_timer_callback(gpointer data);
gboolean te_graph_trigger(gpointer user_data);
void te_update_diff(const char *event, xmlNode *msg);

extern void trigger_graph_processing(const char *fn, int line);
void abort_after_delay(int abort_priority, enum pcmk__graph_next abort_action,
                       const char *abort_text, guint delay_ms);
void abort_transition_graph(int abort_priority,
                            enum pcmk__graph_next abort_action,
                            const char *abort_text, const xmlNode *reason,
                            const char *fn, int line);

#  define trigger_graph()	trigger_graph_processing(__func__, __LINE__)
#  define abort_transition(pri, action, text, reason)			\
	abort_transition_graph(pri, action, text, reason,__func__,__LINE__);

extern crm_trigger_t *transition_trigger;

extern char *failed_stop_offset;
extern char *failed_start_offset;

void te_action_confirmed(pcmk__graph_action_t *action, pcmk__graph_t *graph);
void te_reset_job_counts(void);

#endif
