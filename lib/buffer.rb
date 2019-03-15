# frozen_string_literal: true

require 'buffer/version'
require 'buffer/ops'
require 'buffer/buffer'

module Buffer
  extend self

  def create(back)
    Buffer::Buffer.new(back)
  end
end
