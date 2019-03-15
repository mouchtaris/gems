module Buffer
  module Ops
    def heading
      pos - start
    end

    def remaining
      lim - pos
    end
    alias_method :size, :remaining
    alias_method :length, :size

    def tailing
      self.end - lim
    end

    def capacity
      # heading + remaining + tailing
      self.end - start
    end

    def each
      return to_enum.lazy unless block_given?
      back
        .drop(heading)
        .take(remaining)
        .each { |elem| yield elem }
    end

    def [](i = 0)
      each.drop(i).first
    end
    alias_method :first, :[]

    def join(sep = '')
      each.reduce(nil) { |s, el| if s then s + sep + el.to_s else el.to_s end }
    end

    def sub(from = 0, n = nil)
      pos2 = pos + from
      lim2 = pos2 + (n || remaining - from)
      copy pos: pos2, lim: lim2
    end
    alias_method :drop, :sub

    def take(n)
      sub(0, n)
    end

    def take_while
      return enum_for(:take_while),lazy unless block_given?
      i = each.reduce(0) { |i, elem| if yield elem then i + 1 else break i end }
      [take(i), drop(i)]
    end

    def include?(*args, &block)
      each.include?(*args, &block)
    end

    def inspect
      "<Buffer>[#{join(', ')}]"
    end
  end
end
