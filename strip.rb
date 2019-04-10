#!/usr/bin/env ruby
# frozen_string_literal: true
require 'pp'

Striput = <<-STRIP
           
   
      
      | Oh lala
          | Ti oraiaw ti kala
| Oh alla
            |                     
                .
          |    

  
,   
|
  STRIP

public

def to_range
  self[0]..self[1]
end

def set_fg(col)
  "\x1b[38;5;#{col}m"
end

def rs
  "\x1b[0m"
end

def color(col)
  -> (arg = nil) {
    set_fg(col) + (arg || self).to_s + rs
  }
end

define_method :warpink, &color(215)
define_method :lime, &color(149)
define_method :surger, &color(75)

def barstrip(bar = '|', circus: nil)
  rx = /(\A\s*)?^[ \t]*#{Regexp.escape bar}[ \t]?/
  source = to_s.dup
  destination = ''
  sepa = ':'.warpink.freeze
  last_post = nil
  while md = rx.match(source)
    destination += md.pre_match

    (md.length - 1 - (md.length - 1)).downto(0).each do |i|
      repl = md[i].inspect
      destination +=
        case circus
        when true then sepa + i.to_s + sepa + repl.lime
        else ''
        end
    end

    source = md.post_match
  end
  destination += source
  destination
end

#Striput.barstrip == "Oh lalaTi oraiaw ti kalaOh alla                    \n                .   \n\n  \n,   \n" || (raise)

puts STDIN.read.barstrip if __FILE__ == $0
