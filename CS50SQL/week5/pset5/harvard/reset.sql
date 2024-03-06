-- For enrollments
DROP INDEX IF EXISTS "enrollments_students";

DROP INDEX IF EXISTS "enrollments_courses";

-- For courses
DROP INDEX IF EXISTS "courses_department";

DROP INDEX IF EXISTS "courses_semester";

DROP INDEX IF EXISTS "courses_title";

-- For  satisfies
DROP INDEX IF EXISTS "satisfies_course";

DROP INDEX IF EXISTS "satisfies_requirement";