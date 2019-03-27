module Util
  class LazyBlock
    def initialize(proc_, *args, **opts, &block)
      @proc = proc_.freeze || (raise ArgumentError, 'proc_ is nil')
      @args = (args || []).freeze
      @opts = (opts || {}).freeze
      @block = block.freeze
    end

    def call(*extra_args, **extra_opts, &extra_block)
      total_args = @args&.+(extra_args || []) || extra_args
      total_opts = @opts&.merge(extra_opts || {}) || extra_opts
      total_block = @block || extra_block
      if total_opts&.empty? == false
        @proc.call(*total_args, **total_opts, &total_block)
      else
        @proc.call(*total_args, &total_block)
      end
    end

    def to_proc
      self
    end
  end
end
