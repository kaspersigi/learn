#include <stdio.h>

enum object_type { STUDENT,
    TEACHER,
    WORKER,
};

typedef struct student_object {
    enum object_type type;
    int grade;
    int score;
} student_object;

typedef struct teacher_object {
    enum object_type type;
    int rank;
    int suject;
} teacher_object;

typedef struct worker_object {
    enum object_type type;
    int salary;
    int hour;
} worker_object;

typedef union people_object {
    struct student_object so;
    struct teacher_object to;
    struct worker_object wo;
} people_object;

int main(int argc, char* argv[])
{
    teacher_object to = { TEACHER, 20, 30 };
    student_object so = { STUDENT, 6, 100 };
    worker_object wo = { WORKER, 5000, 8 };
    people_object po = { so };

    switch (po.to.type) {
    case TEACHER:
        printf("rank = %d, subject = %d\n", po.to.rank, po.to.suject);
        break;
    case STUDENT:
        printf("grade = %d, score = %d\n", po.so.grade, po.so.score);
        break;
    case WORKER:
        printf("hour = %d, salary = %d\n", po.wo.hour, po.wo.salary);
        break;

    default:
        break;
    }

    return 0;
}