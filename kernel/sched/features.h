/*
 * Only give sleepers 50% of their service deficit. This allows
 * them to run sooner, but does not allow tons of sleepers to
 * rip the spread apart.
 */
#define SCHED_FEAT_GENTLE_FAIR_SLEEPERS 1

/*
 * Place new tasks ahead so that they do not starve already running
 * tasks
 */
#define SCHED_FEAT_START_DEBIT 1

/*
 * Prefer to schedule the task we woke last (assuming it failed
 * wakeup-preemption), since its likely going to consume data we
 * touched, increases cache locality.
 */
#define SCHED_FEAT_NEXT_BUDDY 0

/*
 * Prefer to schedule the task that ran last (when we did
 * wake-preempt) as that likely will touch the same data, increases
 * cache locality.
 */
#define SCHED_FEAT_LAST_BUDDY 1

/*
 * Consider buddies to be cache hot, decreases the likelyness of a
 * cache buddy being migrated away, increases cache locality.
 */
#define SCHED_FEAT_CACHE_HOT_BUDDY 1

/*
 * Allow wakeup-time preemption of the current task:
 */
#define SCHED_FEAT_WAKEUP_PREEMPTION 1

#define SCHED_FEAT_HRTICK 0
#define SCHED_FEAT_DOUBLE_TICK 0
#define SCHED_FEAT_LB_BIAS 1

/*
 * Decrement CPU capacity based on time not spent running tasks
 */
#define SCHED_FEAT_NONTASK_CAPACITY 1

/*
 * Queue remote wakeups on the target CPU and process them
 * using the scheduler IPI. Reduces rq->lock contention/bounces.
 */
<<<<<<< HEAD
SCHED_FEAT(TTWU_QUEUE, true)
=======
#define SCHED_FEAT_TTWU_QUEUE 0
>>>>>>> 7670dce579b1 (sched: Resolve sched_feat() at compile time to improve code optimization)

#ifdef HAVE_RT_PUSH_IPI
/*
 * In order to avoid a thundering herd attack of CPUs that are
 * lowering their priorities at the same time, and there being
 * a single CPU that has an RT task that can migrate and is waiting
 * to run, where the other CPUs will try to take that CPUs
 * rq lock and possibly create a large contention, sending an
 * IPI to that CPU and let that CPU push the RT task to where
 * it should go may be a better scenario.
 */
#define SCHED_FEAT_RT_PUSH_IPI 1
#else
#define SCHED_FEAT_RT_PUSH_IPI 0
#endif

#define SCHED_FEAT_FORCE_SD_OVERLAP 0
#define SCHED_FEAT_RT_RUNTIME_SHARE 0
#define SCHED_FEAT_LB_MIN 0
#define SCHED_FEAT_ATTACH_AGE_LOAD 1

/*
 * HMP scheduling. Use dynamic threshold depends on system load and
 * CPU capacity to make schedule decisions.
 */
<<<<<<< HEAD
#ifdef CONFIG_SCHED_HMP
SCHED_FEAT(SCHED_HMP, true)
#else
SCHED_FEAT(SCHED_HMP, false)
#endif
=======
#define SCHED_FEAT_UTIL_EST 1
#define SCHED_FEAT_UTIL_EST_FASTUP 1
>>>>>>> 7670dce579b1 (sched: Resolve sched_feat() at compile time to improve code optimization)

/*
 * Energy aware scheduling. Use platform energy model to guide scheduling
 * decisions optimizing for energy efficiency.
 */
<<<<<<< HEAD
#ifdef CONFIG_MTK_SCHED_EAS_PLUS
SCHED_FEAT(ENERGY_AWARE, true)
=======
#ifdef CONFIG_DEFAULT_USE_ENERGY_AWARE
#define SCHED_FEAT_ENERGY_AWARE 1
>>>>>>> 7670dce579b1 (sched: Resolve sched_feat() at compile time to improve code optimization)
#else
#define SCHED_FEAT_ENERGY_AWARE 0
#endif

/*
<<<<<<< HEAD
=======
 * Minimum capacity capping. Keep track of minimum capacity factor when
 * minimum frequency available to a policy is modified.
 * If enabled, this can be used to inform the scheduler about capacity
 * restrictions.
 */
#define SCHED_FEAT_MIN_CAPACITY_CAPPING 1

/*
 * Energy aware scheduling algorithm choices:
 * EAS_PREFER_IDLE
 *   Direct tasks in a schedtune.prefer_idle=1 group through
 *   the EAS path for wakeup task placement. Otherwise, put
 *   those tasks through the mainline slow path.
 */
#define SCHED_FEAT_EAS_PREFER_IDLE 1

/*
>>>>>>> 7670dce579b1 (sched: Resolve sched_feat() at compile time to improve code optimization)
 * Enforce the priority of candidates selected by find_best_target()
 * ON: If the target CPU saves any energy, use that.
 * OFF: Use whichever of target or backup saves most.
 */
<<<<<<< HEAD
SCHED_FEAT(FBT_STRICT_ORDER, false)
=======
#define SCHED_FEAT_FBT_STRICT_ORDER 0

/*
 * Apply schedtune boost hold to tasks of all sched classes.
 * If enabled, schedtune will hold the boost applied to a CPU
 * for 50ms regardless of task activation - if the task is
 * still running 50ms later, the boost hold expires and schedtune
 * boost will expire immediately the task stops.
 * If disabled, this behaviour will only apply to tasks of the
 * RT class.
 */
#define SCHED_FEAT_SCHEDTUNE_BOOST_HOLD_ALL 0
>>>>>>> 7670dce579b1 (sched: Resolve sched_feat() at compile time to improve code optimization)
