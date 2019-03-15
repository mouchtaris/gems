module Buffer
  class Buffer
    include BufferOps
    attr_reader :back, :start, :pos, :lim, :end
    Positions = %i[ start end pos lim ].freeze

    def initialize(back)
      @back = back.to_enum.lazy
      @start = @pos = 0
      @end = @lim = back.size
    end

    def validate!
      raise 'start > pos' unless @start <= @pos
      raise 'pos > lim' unless @pos <= @lim
      raise 'lim > end' unless @lim <= @end
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
