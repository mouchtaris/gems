module Buffer
  class Buffer
    include Ops
    attr_reader :back, :start, :pos, :lim, :end
    Positions = %i[ start end pos lim ].freeze

    def initialize(back)
      @count = # caching kinda
        (back.respond_to?(:size) && back.size) ||
          back.count
      @back = back.to_enum.lazy
      @start = @pos = 0
      @end = @lim = @count
    end

    def validate!
      raise 'start > pos' unless @start <= @pos
      raise 'pos > lim' unless @pos <= @lim
      raise 'lim > end' unless @lim <= @end
      raise 'start < 0' unless @start >= 0
      raise 'end > count' unless @end <= @count
    end

    def copy(**params)
      result = dup
      Positions.each do |name|
        var_name = :"@#{name}"
        value = params[name]
        result.instance_variable_set(var_name, value) if value
      end
      result.validate!
      result
    end
  end
end
