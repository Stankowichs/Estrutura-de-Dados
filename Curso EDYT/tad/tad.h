
typedef struct float_vector FloatVector;

FloatVector *createVector(int capacity);
void destroyVec(FloatVector **vec_ref);
int size(FloatVector *vec);
int capacity(FloatVector *vec);
float at(FloatVector *vec, int index);
float get(FloatVector *vec, int index);
void set(FloatVector *vec, int index, float val);
void append(FloatVector *vec, float val);
void print(FloatVector *vec);