# C++ Study Archive

A personal collection of small C++ programs I wrote while working through
classic books on the language, the STL, Boost, and design patterns. The
projects span roughly the era of C++98 through C++14 and are preserved
here mostly for sentimental and reference value — they're the code that
taught me C++.

Most subprojects are Visual Studio solutions/projects (`.sln`, `.vcxproj`,
older `.vcproj`); a handful use CMake or plain Makefiles. Many of the
files are example code transcribed or adapted from the source book — see
[Attribution and Licensing](#attribution-and-licensing) below.

## Table of Contents

- [Overview](#overview)
- [Repository Layout](#repository-layout)
- [Building](#building)
- [Sections](#sections)
  - [The C++ Programming Language — 3rd Edition](#the-c-programming-language--3rd-edition)
  - [The C++ Standard Library — A Tutorial and Reference](#the-c-standard-library--a-tutorial-and-reference)
  - [Effective C++ — 2nd Edition](#effective-c--2nd-edition)
  - [Effective C++ — 3rd Edition](#effective-c--3rd-edition)
  - [More Effective C++](#more-effective-c)
  - [Effective STL](#effective-stl)
  - [Effective Modern C++](#effective-modern-c)
  - [Modern C++ Design](#modern-c-design)
  - [Design Patterns Using C++](#design-patterns-using-c)
  - [Designing Components with C++ STL](#designing-components-with-c-stl)
  - [C++ Templates — The Complete Guide](#c-templates--the-complete-guide)
  - [`templates/` — Vandevoorde & Josuttis examples](#templates--vandevoorde--josuttis-examples)
  - [Data Structures Using C++ — Study Guide](#data-structures-using-c--study-guide)
  - [Beyond C++ STL — An Introduction to Boost](#beyond-c-stl--an-introduction-to-boost)
  - [Boost Asio Tutorial](#boost-asio-tutorial)
  - [Boost IOStreams Tutorial](#boost-iostreams-tutorial)
  - [Boost Thread Tutorial](#boost-thread-tutorial)
  - [Meeting-C++-IOStreams](#meeting-c-iostreams)
  - [`xperiment/` — miscellaneous experiments](#xperiment--miscellaneous-experiments)
- [Attribution and Licensing](#attribution-and-licensing)
- [Caveats](#caveats)

## Overview

The repository contains roughly twenty top-level folders, each tied to a
book or tutorial. Inside each you'll find one Visual Studio solution and
many tiny per-topic subprojects (typically a single `.cpp` and the
matching `.vcxproj`). The naming convention follows the source material:
`item_N` for the *Effective* series, descriptive names elsewhere.

## Repository Layout

```
.
├── The C++ Programming Language - 3rd Edition/
├── The C++ Standard Library - A Tutorial and Reference/
├── Effective C++ 2nd Edition/
├── Effective C++ 3rd Edition/
├── More Effective C++/
├── Effective STL/
├── Effective Modern C++/
├── Modern C++ Design/
├── Design Patterns Using C++/
├── Designing Components with C++ STL/
├── C++ Templates - The Complete Guide/
├── templates/                                       (Vandevoorde & Josuttis sources)
├── Data Structures Using C++ - Study Guide/
├── Beyond C++ STL - An Introduction to Boost/
├── Boost Asio Tutorial/
├── Boost IOStreams Tutorial/
├── Boost Thread Tutorial/
├── Meeting-C++-IOStreams/
└── xperiment/                                       (loose experiments)
```

## Building

Most subprojects expect a Windows toolchain:

- **Visual Studio** — open the `.sln` inside any top-level folder. Older
  projects (`.vcproj`) will prompt for an upgrade.
- **Boost** — Boost-dependent projects assume Boost headers and built
  libraries are on the include/lib path. The `Meeting-C++-IOStreams`
  project files explicitly reference `C:\Toolkit\boost_1_54_0`; adjust to
  your installation.
- **CMake** — `Boost IOStreams Tutorial/CMakeLists.txt` and a few Asio
  subprojects build with CMake.
- **Makefiles** — `templates/` uses a plain Makefile (GCC).

Per-user Visual Studio settings (`*.vcxproj.user`) are intentionally not
tracked.

## Sections

### The C++ Programming Language — 3rd Edition

Bjarne Stroustrup's reference book. Subprojects illustrate the core
language features:

- `Exception Handling/`
- `Operator Overloading/`
- `Streams Intro/`
- `Templates/`
- `Traditional Class Hierarchy/`

### The C++ Standard Library — A Tutorial and Reference

Nicolai Josuttis's STL reference. Organised by component family:

- `Containers/` — vector, deque, list, set/map variants, bitset, stack/queue
- `Iterators/` — iterator categories, adaptors, stream iterators
- `FunctionObjects/` — predicates, binders, composers
- `STL Study/` — broader STL exercises
- `Original Book Source Code/` — the publisher's source bundle

### Effective C++ — 2nd Edition

Scott Meyers's first round of advice. One folder per Item that warranted
runnable code (e.g. `item_12`, `item_36`, `item_47`), plus a few
free-standing examples (`Array/`, `Stack/`).

### Effective C++ — 3rd Edition

The C++03-era rewrite. Items implemented:

- `item_3`, `item_6`, `item_12`, `item_24`, `item_35`, `item_39`,
  `item_42`, `item_43`, `item_47`, `item_49`, `item_50`, `item_51`,
  `item_52`.

### More Effective C++

Items 10–14 and 25–29 — the auto-ptr, smart pointer, reference counting,
and proxy-class exercises.

### Effective STL

Selected items focused on STL pitfalls and idioms (`item_12`, `item_14`,
`item_26`, `item_30`, `item_37`–`item_43`, `item_47`). Includes
`estl-examples/` (the publisher's source bundle) and a couple of
hand-written helpers (`ESTLUtil_rewrite.hpp`, `Widget.h`).

### Effective Modern C++

Just one item (`item_1`) — this section never went past the first
chapter.

### Modern C++ Design

Andrei Alexandrescu's policy-based design book. Contains only the
`Command/` example.

### Design Patterns Using C++

Hand-coded "GoF" pattern walk-throughs:

- `Command/`
- `Factory/`
- `Memento/`
- `Singleton/`

### Designing Components with C++ STL

Ulrich Breymann's STL component-design book. Five sections matching the
book's structure:

- `algorithms/`
- `applications/`
- `containers/`
- `iterators/`
- `util/`

### C++ Templates — The Complete Guide

My own walkthrough of Vandevoorde & Josuttis chapters:

- `Function Objects/`
- `Names In Templates/`
- `Templates And Inheritance/`
- `Traits and Policy Classes/`
- `Tricky Basics/`

### `templates/` — Vandevoorde & Josuttis examples

The publisher's complete example source for the same book, kept
separately. Builds with the included `Makefile`. Folders mirror the
book's chapter topics: `basics/`, `details/`, `exprtmpl/`, `functors/`,
`inherit/`, `meta/`, `pointers/`, `poly/`, `traits/`, `tuples/`,
`types/`.

### Data Structures Using C++ — Study Guide

Classic data-structure implementations:

- `linked-list/`, `double-linked-list/`
- `binary_tree/`, `bsearch_tree/`, `red_black_tree/`
- `hash_map/`
- `trie/`
- `unjumble/` — an anagram-solving exercise

### Beyond C++ STL — An Introduction to Boost

Björn Karlsson's Boost intro, with extra material I added later. Roughly
thirty small projects, including:

- Smart pointers: `scoped_ptr_1`, `shared_ptr_1`, `shared_ptr_and_stl`,
  `shared_ptr_pimpl`, `scoped_ptr_pimpl`, `weak_ptr_1`, `weak_ptr_2`,
  `s_ptr_other_resources`
- Type-erasure / variants: `any_1`, `any_more`, `any_out`,
  `any_predicates`, `any_property`, `any_and_shared_ptr`, `variant_1`,
  `tuple_1`
- Casts: `lexical_cast_1`, `numeric_cast_1`, `polymorphic_cast_1`,
  `poly_cast_vs_dyn_cast`
- Signals & callbacks: `boost_signal_1`, `boost_signal_std_lib`,
  `boost_bind_1`
- Logging: `basic_boost_log`, `advanced_boost_log`, `async_boost_log`,
  `settings_file_boost_log`
- Other: `regex_1`, `pool_1`, `program_options_first`, `python_1`,
  `ptr_container_1`, `unordered_1`, `interprocess_1`, `timer`,
  `boost_test_1`, `boost_test_const_string`

### Boost Asio Tutorial

A larger collection drawn from Boost.Asio examples, John Torjo's "Asio
guide", and Alex Ott's `test-otpc` thread-pool examples. Highlights:

- TCP: `tcp_sync`, `daytime_client`/`daytime_server`,
  `iostream_client`/`iostream_server`, `chat_client`/`chat_server`,
  `reference_counted`
- HTTP: `http_client`, `http_server`, `http_server_3`, `http_proxy`
- Multicast: `multicast_sender`, `multicast_receiver`
- Timers: `timer_sync`, `timer_async`, `timer_async_threaded`
- Multi-threaded servers: `multi_thread_multi_connections`, `otpc-mtmc`,
  `test-otpc`
- Serialization / wire formats: `serialization`, `json_serialization`,
  `json_client`, `json_server`, `asio_protobuf_sample`
- Tutorial walkthrough: `guide/` (Torjo's stepwise examples)
- Misc: `logger_services`, `threadpool-0_2_5-doc/`

### Boost IOStreams Tutorial

Two CMake-based filter examples:

- `simple_filter_usage/`
- `shell_comments_filter/`

### Boost Thread Tutorial

Three sets of examples:

- `boost_thread_tutorial/` — `helloworld`, `helloworld2/3/4`, `factorial`,
  `factorial2/3`, `counter`, `once`, `tss`, `bounded_buffer`
- `drdobbs/` — `thread_safe_queue`, `tokenize`, `concurrent_queue`
- `example/` — extra threading sketches

### Meeting-C++-IOStreams

Materials from a Meeting C++ talk on IOStreams (`src/` plus the
companion `.pptx`).

### `xperiment/` — miscellaneous experiments

Loose code that didn't fit a book — early-career playground material:

- I/O & parsing: `binary_files`, `simple_xml`, `effective_xml`,
  `tokenize`, `string_files`, `base64`, `huffman`, `atoi`, `bits_bytes`
- OO mechanics: `access_modifiers`, `polymorphism`, `inheritance`,
  `interfaces`, `simple_base`, `vbase`, `covariant`, `covariant_2`,
  `struct_vs_class`, `const_char_member`, `references`, `explicit`
- Patterns / smart pointers: `policy_observer`, `map_of_shared_ptr`,
  `ptypes_xcess`
- Algorithms / time: `alg_next_perm`, `time`
- Networking: `pinet_client`, `pinet_server`, `pinet_cs`
- Logging: `log4cpp`, `log4cpp_test`, `log4cpp.properties`

## Attribution and Licensing

This repository is a study archive, **not** an original work. It mixes:

- **Original example code from the books** — copyright belongs to the
  respective authors and publishers (Stroustrup, Meyers, Josuttis,
  Alexandrescu, Vandevoorde, Karlsson, Breymann, et al.). These files
  are included here for personal study under the permissive terms most
  of these books grant for non-commercial educational use; original
  copyright notices have been preserved where present (see, e.g.,
  `templates/README`).
- **Third-party example projects** — credited in their source headers,
  notably Alex Ott (Asio examples) and Eli Bendersky (Asio + protobuf).
- **My own code** — small explorations, modifications, and exercises
  built on top of the above.

My own contributions are released under the MIT License (see
[`LICENSE`](LICENSE)). The book- and third-party-derived files remain
the property of their respective authors and publishers and are
governed by each original source's terms — the MIT grant does **not**
extend to them.

## Caveats

- The code is old. Most of it predates C++11; some predates even
  `std::shared_ptr`. Style and idioms reflect the era of the source
  material, not modern best practice.
- Build files target Visual Studio versions ranging from VS 2008
  (`.vcproj`) up to VS 2015+ (`.vcxproj`). Expect upgrade prompts and
  the occasional missing dependency.
- Hard-coded Boost paths (e.g. `C:\Toolkit\boost_1_54_0`) will need to be
  edited for your environment.
- This is preserved as a snapshot of how I learned C++ — bugs,
  inconsistencies, and dead-ends included.
