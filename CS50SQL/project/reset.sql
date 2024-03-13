DROP INDEX IF EXISTS idx_title_title;

DROP INDEX IF EXISTS idx_title_release_date;

DROP INDEX IF EXISTS idx_genre_name;

DROP INDEX IF EXISTS idx_companies_name;

DROP INDEX IF EXISTS idx_title_genre_title_id;

DROP INDEX IF EXISTS idx_title_genre_genre_id;

DROP INDEX IF EXISTS idx_title_companies_title_id;

DROP INDEX IF EXISTS idx_title_companies_company_id;

DROP INDEX IF EXISTS idx_title_crew_title_id;

DROP INDEX IF EXISTS idx_title_crew_crew_id;

DROP INDEX IF EXISTS idx_title_cast_title_id;

DROP INDEX IF EXISTS idx_title_cast_crew_id;

DROP INDEX IF EXISTS idx_person_name;

DROP INDEX IF EXISTS idx_crew_role;

DROP INDEX IF EXISTS idx_cast_role;

DROP VIEW IF EXISTS title_summary;

DROP TABLE IF EXISTS title_genre;

DROP TABLE IF EXISTS title_companies;

DROP TABLE IF EXISTS title_crew;

DROP TABLE IF EXISTS title_cast;

DROP TABLE IF EXISTS genre;

DROP TABLE IF EXISTS companies;

DROP TABLE IF EXISTS title;

DROP TABLE IF EXISTS person;

DROP TABLE IF EXISTS crew;

DROP TABLE IF EXISTS cast;