#ifndef __LIST_UTIL_H__
#define __LIST_UTIL_H__

#define LIST_CREATE(type, lh) type lh = {.next = &lh, .prev = &lh}

// @_p, @_q: iterators
// @_h: head node
// @_s: start node pointer
#define list_for_each(_p, _h) for (_p = _h.next; _p != &_h; _p = _p->next)
#define list_init(_h)                                                          \
  do {                                                                         \
    _h.next = _h.prev = &_h;                                                   \
  } while (0)
#define list_add_tail(_p, _s)                                                  \
  do {                                                                         \
    (_p)->next       = &(_s);                                                  \
    (_p)->prev       = (_s).prev;                                              \
    (_s).prev        = (_p);                                                   \
    (_p)->prev->next = (_p);                                                   \
  } while (0)
#define list_del(_p)                                                           \
  do {                                                                         \
    _p->next->prev = _p->prev;                                                 \
    _p->prev->next = _p->next;                                                 \
  } while (0)
#define list_del_all(_p, _q, _h)                                               \
  for (_p = _h.next; _p != &_h; _q = _p->next, free(_p), _p = _q)
#define list_for_del(_p, _h) for (_p = _h.next; _p != &_h;)
#define list_for_del_next(_p, _q)                                              \
  do {                                                                         \
    _q = _p;                                                                   \
    _p = _p->next;                                                             \
  } while (0)

#define list_empty(_h) ((_h).next == &(_h))

#define list_shift(_p, _h)                                                     \
  do {                                                                         \
    _p = (_h).next;                                                            \
    list_del(_p);                                                              \
  } while (0)

#define get_lock(lock) while (__sync_fetch_and_or(&(lock), 1))
#define put_lock(lock)                                                         \
  do {                                                                         \
    lock = 0;                                                                  \
  } while (0)

#endif // __LIST_UTIL_H__
