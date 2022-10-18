# DSA-comment-section / ASP Koment sekcija
## *Data Structures and Algorithms comment section project - serbian edition*

`SRB`
Ova jednostavna konzolna aplikacija objedinjuje `inorder` i `preorder` obilaske **n-arnih stabala** na primeru jednostavne koment sekcije.
Iako odradjena u konzoli, aplikacija u potpunosti simulira rad komentara na socijalnim mrezama:

- Dodavanje/brisanje txt postova
- Dodavanje/brisanje komentara na post, ili komentara na komentare (lancano komentarisanje)
- 'Like' sistem - sistem reagovanja na post/komentar dodavanjem poena na komentar. Dozvoljeni su i negativni bodovi
- Rangiranje po broju poena
- Rangiranje celih sekcija po broju poena

Projekat koristi strukture podataka i funkcije iz C++ STL biblioteke (vector, iterator...).

`ENG`
This simple console application combines `inorder` and `preorder` traversals of **n-ary trees** on the example of a simple comment section.
Although done in the console, the application fully simulates the work of comments on social networks:

- Adding/deleting txt posts
- Adding/deleting comments on a post, or comments on comments (chain commenting)
- 'Like' system - a system of reacting to a post/comment by adding points to the comment. Negative points are also allowed
- Ranking by number of points
- Ranking of entire sections by number of points

Project uses data structures and functions from C++ STL (vector, iterator...).

## Future commits - job to be done

Several things should be added:
- Change C-like errors handling with C++ Exceptions **(high priority)**
- Add references: one comment from one section can have references to other comments from different sections
