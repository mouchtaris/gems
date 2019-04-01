module Colourtable
  module Colourize
    # colorization
    def colorize(color_code)
      "\e[#{color_code}m#{self}\e[0m"
    end

    def red
      colorize(31)
    end

    def green
      colorize(32)
    end

    def yellow
      colorize(33)
    end

    def blue
      colorize(34)
    end

    def pink
      colorize(35)
    end

    def light_blue
      colorize(36)
    end
  end

  class String < ::String
    include Colourize
    class << self
      def from(str)
        String.new(str)
      end
    end
  end

  #outputs color table to console, regular and bold modes
  module_function def colortable
    names = %w(black red green yellow blue pink cyan white default)
    fgcodes = (30..39).to_a - [38]

    s = ''
    reg  = "\e[%d;%dm%s\e[0m"
    bold = "\e[1;%d;%dm%s\e[0m"
    puts '                       color table with these background codes:'
    puts '          40       41       42       43       44       45       46       47       49'
    names.zip(fgcodes).each {|name,fg|
      s = "#{fg}"
      puts "%7s "%name + "#{reg}  #{bold}   "*9 % [fg,40,s,fg,40,s,  fg,41,s,fg,41,s,  fg,42,s,fg,42,s,  fg,43,s,fg,43,s,  
        fg,44,s,fg,44,s,  fg,45,s,fg,45,s,  fg,46,s,fg,46,s,  fg,47,s,fg,47,s,  fg,49,s,fg,49,s ]
    }
  end
end
