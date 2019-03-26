module Util
  class LazyBlock
    def initialize(proc_, *args, **opts, &block)
      @proc = proc_ || (raise ArgumentError, 'proc_ is nil')
      @args = args || []
      @opts = opts || {}
      @block = block
    end

    def call(*extra_args, **extra_opts, &extra_block)
      @proc.call(
        *(@args.concat(extra_args || [])),
        **(@opts.merge(extra_opts || {})),
        &(@block || extra_block || ->(*){})
      )
    end

    def to_proc
      self
    end
  end
end
