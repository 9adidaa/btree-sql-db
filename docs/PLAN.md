# 🧠 Project Roadmap – Mohamed Mokdad – `btree-sql-db`

---

## ✅ STEP 1: Project Setup – ✅ Done
- [x] Created GitHub repo
- [x] Created project structure: `src/`, `tests/`, `data/`, `docs/`
- [x] Wrote `README.md`, `author.md`, `.gitignore`
- [x] Added `Makefile` with proper compiler flags

---

## ✅ STEP 2: Design Phase – ✅ Done
- [x] Defined `Row`, `BTreeNode`, and `Table` structs in `btree.h`
- [x] Designed the command structure in `docs/commands.md`
- [x] Listed function prototypes (insert, search, delete)

---

## ✅ STEP 3: B-tree Insert Logic

### ✔️ 3A – Insert into empty tree → ✅ Done
- Function: `insert_node()`
- Creates root node if tree is empty
- Test written and passing

### ✔️ 3B – Insert into non-full leaf node → ✅ Done
- Sorted insert in a non-full root node
- Test written and passing

### ⏳ 3C – Insert with root node split → 🔜 Next step
- When root is full, split it and create a new root
- Handle shifting keys and children

---

## ⏳ STEP 4: Insert/Search/Delete Recursively
- [ ] Implement insert that recurses down the tree
- [ ] Add proper split at internal node level
- [ ] Implement `search_node()`
- [ ] Implement `delete_node()` (basic version)

---

## ⏳ STEP 5: Command Parsing (SQL-Like Commands)
- [ ] `INSERT INTO table VALUES (...)`
- [ ] `SELECT * FROM table WHERE id=...`
- [ ] `DELETE FROM table WHERE id=...`

We'll write a basic REPL loop in `main.c` for that.

---

## ⏳ STEP 6: Persistence
- [ ] Save tree to file (`data/db.bin`)
- [ ] Load from file on startup

---

## ⏳ STEP 7: Testing
- [ ] More unit tests (deep tree, duplicate inserts, deletes)
- [ ] Test persistence (save/load works)

---

## ⏳ STEP 8: Documentation & Final Touches
- [ ] Update `README.md` with usage examples
- [ ] Final commit + push
- [ ] (Optional) Add `valgrind` or sanitizers for bonus
