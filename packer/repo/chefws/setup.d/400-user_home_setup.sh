true &&
  source <(echo 'export PATH="$PATH:$HOME/.local/bin"' | tee -a $HOME/.bashrc) &&
  pip install --user httpie &&
  true
