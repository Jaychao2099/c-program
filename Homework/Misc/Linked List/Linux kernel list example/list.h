/* Linux-like double-linked list implementation */
#ifndef MY_LIST_H
#define MY_LIST_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/* "typeof" is a GNU extension.
 * Reference: https://gcc.gnu.org/onlinedocs/gcc/Typeof.html
 */
#if defined(__GNUC__)
#define __LIST_HAVE_TYPEOF 1
#endif


#ifndef container_of
#ifdef __LIST_HAVE_TYPEOF


/* container_of() - Calculate address of object that contains address ptr
 * @ptr: pointer to member variable
 * @type: type of the structure containing ptr
 * @member: name of the member variable in struct @type
 * Return: @type pointer of object containing ptr
 * 
 */
 
/* 一般實作的 container_of 巨集定義，包含了型別檢查的功能
 * __extension__ 標注，避免 GCC 搭配 -pedantic (檢查是否用到 C89/C90 以外的特徵) 編譯選項時，會拋出警告訊息。 (非必要)
 * 透過 __typeof__ 取得 ptr 的型別，並宣告 __pmember 為該型別的指標，並將 ptr 指向的位址(member 的位址)賦值給 __pmember。
 * 在編譯期確認 ptr 的類型和 type->member 相容，否則報錯。
 * 將 __pmember 減去 member 在 type 中的位移量 (用char *，確保計算正確)，得到 type 的位址，並轉型為 type 型別的指標，最後回傳該指標。
 */
#define container_of(ptr, type, member)                                 \
    __extension__({                                                     \
        const __typeof__(((type *) 0)->member) *(__pmember) = (ptr);    \
        (type *)((char *)__pmember - offsetof(type, member));           \
    })

/* Linux 核心原始程式碼提供的 container_of 巨集定義事實上更複雜 */

// 達到 static assert 的作用，儘量在編譯時期就查驗 container_of 巨集的使用是否合法：預先進行指標型態的檢查
#define BUILD_BUG_ON_MSG(condition, msg)    \
    do {                                    \
        if (condition) {		            \
            fprintf(stderr, "%s\n", msg);   \
            abort();                        \
        }                                   \
    } while (0)

/* Are two types/vars the same type (ignoring qualifiers)? */
#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

// 任何 GNU C 模式下，默認把 void * 的算術運算視為合法的，這是 GCC 的擴展行為
#define container_of_Linux(ptr, type, member) 				        \
    __extension__({void *__mptr = (void *)(ptr);					\
    BUILD_BUG_ON_MSG(!__same_type(*(ptr), ((type *)0)->member) &&	\
                     !__same_type(*(ptr), void),			        \
                     "pointer type mismatch in container_of()");	\
    ((type *)(__mptr - offsetof(type, member)));                    \
    })

#else
/* 簡易版的 container_of 巨集定義，沒有檢查指標型別是否正確 */
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))
#endif
#endif

struct list_head { struct list_head *prev, *next; };

typedef struct {
    char *value;
    struct list_head list;
} my_data;

// 宣告一個 linked list 的頭部，並初始化 prev 和 next 指向自己
#define LIST_HEAD(head) struct list_head head = {&(head), &(head)}

// 僅初始化 linked list 的頭部，prev 和 next 指向自己
static inline void INIT_LIST_HEAD(struct list_head *head) {
    head->next = head;
    head->prev = head;
}

// Calculate address of entry that contains list node
// container_of 等價的包裝，符合以 list_ 開頭的命名慣例
#define list_entry(node, type, member) container_of_Linux(node, type, member)

// 取得 linked list 的開頭的 entry
#define list_first_entry(head, type, member) \
    list_entry((head)->next, type, member)

// 取得 linked list 的結尾的 entry
#define list_last_entry(head, type, member) \
    list_entry((head)->prev, type, member)

// iterate over list nodes
// 注意: node 和 head 不能在迴圈中被更改 (可能在多工環境中出現)，否則行為不可預期
#define list_for_each(node, head) \
    for (node = (head)->next; node != (head); node = node->next)

/* 走訪包含 struct list_head 的另外一個結構之 entry。
 * 注意: entry 和 head 不能在迴圈中被更改，否則行為不可預期。
 * 因為 typeof 之限制，只能在 GNUC 下使用
 */
#ifdef __LIST_HAVE_TYPEOF
#define list_for_each_entry(entry, head, member)                            \
    for (entry = list_entry((head)->next, __typeof__(*entry), member);      \
         &entry->member != (head);                                          \
         entry = list_entry(entry->member.next, __typeof__(*entry), member))
#endif
/* 透過額外的 safe 紀錄每個迭代 (iteration) 所操作的節點的下一個節點，因此目前的節點可允許被移走
 * 其他操作則同為不可預期行為
 */
#define list_for_each_safe(node, safe, head)                     \
    for (node = (head)->next, safe = node->next; node != (head); \
         node = safe, safe = node->next)
         
#define list_for_each_entry_safe(entry, safe, head, member)                \
    for (entry = list_entry((head)->next, __typeof__(*entry), member),     \
         safe = list_entry(entry->member.next, __typeof__(*entry), member);\
         &entry->member != (head); entry = safe,                           \
         safe = list_entry(safe->member.next, __typeof__(*entry), member))

static inline void list_add(struct list_head *node, struct list_head *head) {
    struct list_head *next = head->next;

    next->prev = node;
    node->next = next;
    node->prev = head;
    head->next = node;
}

static inline void list_add_tail(struct list_head *node, struct list_head *head) {
    struct list_head *prev = head->prev;

    prev->next = node;
    node->next = head;
    node->prev = prev;
    head->prev = node;
}
/* LIST_POISONING 巨集一旦定義，將讓已被移走的 node 節點再存取時，觸發作業系統的例外狀況：
 * 對於 next 或者 prev 的存取，會觸發執行時期的 invalid memory access(若系統禁止 predefined memory access)。
 */
static inline void list_del(struct list_head *node) {
    struct list_head *next = node->next;
    struct list_head *prev = node->prev;

    next->prev = prev;
    prev->next = next;

#ifdef LIST_POISONING
    node->prev = (struct list_head *) (0x00100100);
    node->next = (struct list_head *) (0x00200200);
#endif
}

// 移除的 node 會額外呼叫 INIT_LIST_HEAD 把 prev 和 next 指向自身
static inline void list_del_init(struct list_head *node) {
    list_del(node);
    INIT_LIST_HEAD(node);
}

// 檢查 head 的 next 是否指向自身，確認 list 是否為 empty 狀態
static inline int list_empty(const struct list_head *head) {
    return (head->next == head);
}

// 若 head 非 empty 狀態且 prev 和 next 是同一個節點，表示 linked list 只有一個節點
static inline int list_is_singular(const struct list_head *head) {
    return (!list_empty(head) && head->prev == head->next);
}

/* 將 list 的所有 node 都插入到 head 的開始 / 結束位置中。
 * 注意: list 本身仍維持原貌。
*/
static inline void list_splice(struct list_head *list, struct list_head *head) {
    struct list_head *head_first = head->next;
    struct list_head *list_first = list->next;
    struct list_head *list_last = list->prev;

    if (list_empty(list))
        return;

    head->next = list_first;
    list_first->prev = head;

    list_last->next = head_first;
    head_first->prev = list_last;
}

static inline void list_splice_tail(struct list_head *list,
                                    struct list_head *head) {
    struct list_head *head_last = head->prev;
    struct list_head *list_first = list->next;
    struct list_head *list_last = list->prev;

    if (list_empty(list))
        return;

    head->prev = list_last;
    list_last->next = head;

    list_first->prev = head_last;
    head_last->next = list_first;
}

// 移除的 list 會額外呼叫 INIT_LIST_HEAD 把 prev 和 next 指向自身
static inline void list_splice_init(struct list_head *list,
                                    struct list_head *head) {
    list_splice(list, head);
    INIT_LIST_HEAD(list);
}

static inline void list_splice_tail_init(struct list_head *list,
                                         struct list_head *head) {
    list_splice_tail(list, head);
    INIT_LIST_HEAD(list);
}


/* 將從 head_from 的第一個節點到 node 間的一系列節點都移動到 head_to 上。
 * head_to 必須是 empty 狀態 (next 和 prev 都指向自己)，否則可能發生 memory leak。
 */
static inline void list_cut_position(struct list_head *head_to,
                                     struct list_head *head_from,
                                     struct list_head *node) {
    struct list_head *head_from_first = head_from->next;

    if (list_empty(head_from))
        return;

    if (head_from == node) {
        INIT_LIST_HEAD(head_to);
        return;
    }

    head_from->next = node->next;
    head_from->next->prev = head_from;

    head_to->prev = node;
    node->next = head_to;
    head_to->next = head_from_first;
    head_to->next->prev = head_to;
}

// 將 node 從原本的 linked list 移動到另一個 linked list head 的開頭或尾端
static inline void list_move(struct list_head *node, struct list_head *head) {
    list_del(node);
    list_add(node, head);
}

static inline void list_move_tail(struct list_head *node,
                                  struct list_head *head) {
    list_del(node);
    list_add_tail(node, head);
}

#undef __LIST_HAVE_TYPEOF
#ifdef __cplusplus
}
#endif
#endif /* MY_LIST_H */

// int main() {
//     LIST_HEAD(my_list);
//     my_data *data1 = malloc(sizeof(my_data));
//     data1->value = "Hello";
//     list_add(&data1->list, &my_list);

//     my_data *data2 = malloc(sizeof(my_data));
//     data2->value = "World";
//     list_add_tail(&data2->list, &my_list);

//     my_data *entry;
//     list_for_each_entry(entry, &my_list, list) {
//         printf("%s\n", entry->value);
//     }

//     // 釋放記憶體
//     list_for_each_entry_safe(entry, entry, &my_list, list) {
//         free(entry);
//     }

//     return 0;
// }
// // 這段程式碼展示了如何使用 linked list 的基本操作，包括新增、刪除、遍歷等功能。