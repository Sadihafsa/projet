projet se
sadi hafsa amel G:2

Réponses aux questions :
Q1: Quelles sont les structures de données à utiliser ?

Matrices (B, C, A) : Structures de données bidimensionnelles pour stocker les matrices.
Tampon (Buffer) T : Tableau utilisé pour stocker temporairement les résultats.
Sémaphores (empty, full) : Utilisées pour contrôler l'accès au tampon.
Mutex (mutex) : Utilisé pour éviter les conflits d'accès lors de l'insertion et de la consommation dans le tampon.
Q2: Comment allez-vous protéger l'accès à ces données?

Matrices (B, C, A) : L'accès est implicite car chaque thread travaille sur des parties distinctes des matrices.

Tampon (Buffer) T : Protégé par sémaphores et un mutex. Les sémaphores contrôlent l'accès au tampon (attente si vide ou plein), et le mutex garantit un accès exclusif lors de l'insertion et de la consommation.

Q3: Quels sont les risques?

Conditions de concurrence : Risque lorsque plusieurs threads accèdent simultanément au tampon. Les sémaphores et le mutex sont utilisés pour éviter cela.

Dépassement de tampon : Risque si le producteur est plus rapide que le consommateur. Géré par les sémaphores et peut nécessiter une gestion appropriée de la production/consommation.

Synchronisation incorrecte : Risque d'obtenir des résultats incorrects dans la matrice A si la synchronisation entre les threads est incorrecte. Utilisation correcte des sémaphores et du mutex est essentielle.
