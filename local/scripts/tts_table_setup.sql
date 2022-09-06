CREATE TABLE tts (
    tts_id INTEGER PRIMARY KEY AUTOINCREMENT,
    text TEXT NOT NULL,
    audio_file_name TEXT NOT NULL,
    user_id INTEGER NOT NULL,
    FOREIGN KEY(user_id) REFERENCES user(user_id)
);

PRAGMA foreign_keys = ON;
