require_relative '../colourtable'

class ::String
  include Colourtable::Colourize
end
