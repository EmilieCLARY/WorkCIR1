<!DOCTYPE html>
<html lang="fr" dire="ltr">
<head>
    <meta charset="UTF-8">
    <title>blog - accès réservé</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <!-- Ne pas indexer sur les moteurs de recherche -->
    <meta name="robots" content="noindex, nofollow">
    <!-- CSS Font Awesome -->
    <link rel="stylesheet" href="../vendor/fontawesome/css/all.min.css">
    <!-- CSS Bootstrap -->
    <link rel="stylesheet" href="../vendor/bootstrap/css/bootstrap.min.css">
    <!-- CSS perso-->
    <link rel="stylesheet" href="style.css" media="all">
</head>


<body class="login">
    <main class="container">
        <div class="text-center">
            <a href="index.php"><img src="img/logo.png" alt="Blog administration"></a>
        </div>
        <form method="post">
            <fieldset class="form-group">
                <legend>Espace réservé</legend>
                <div class="form-group">
                    <input id="pseudo" class="form-control" name="pseudo" type="text" placeholder="Votre pseudo" 
                    value="<?php echo $pseudo ?>" minlenght="3" maxlenght="20" required>
                </div>
                <div class="form-group">
                    <input id="mdp" class="form-control" name="mdp" type="password" placeholder="Votre mot de passe" 
                    value="<?php echo $mdp ?>" minlenght="8" maxlenght="30" required>
                </div>
                
                <div class="form-group">
                    <button type="submit" class="btn btn-primary btn-block">Se connecter 
                    <i class="fas fa-sign-in-alt"></i></button>
                </div>


                <div class="p-2 clearfix">
                    <a href="#" class="float-left">Mot de passe oublié</a>
                    <a href="#" class="float-right">Créer un compte</a>
                </div>
            </fieldset>
        
        </form>
    </main>
    <footer class="fixed-bottom">
        <p>&copy 2021 Emilie CLARY</p>
    </footer>
</body>
</html>