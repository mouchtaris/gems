require 'cpp/name'

module Parse
  class Filesystem
    def open(name)
      Cpp::Name::Deco.new(name)
    end
  end
end
