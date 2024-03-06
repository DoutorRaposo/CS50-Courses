-- For enrollments
CREATE INDEX "enrollments_students" ON "enrollments" ("student_id", "course_id");

CREATE INDEX "enrollments_courses" ON "enrollments" ("course_id");

-- For courses
CREATE INDEX "courses_department" ON "courses" ("department");

CREATE INDEX "courses_semester" ON "courses" ("semester", "department", "number");

CREATE INDEX "courses_title" ON "courses" ("title");

-- For  satisfies
CREATE INDEX "satisfies_course" ON "satisfies" ("course_id");

CREATE INDEX "satisfies_requirement" ON "satisfies" ("requirement_id");